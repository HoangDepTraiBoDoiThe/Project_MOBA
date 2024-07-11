// Cu Nhat Hoang


#include "Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "ThumbnailHelpers.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Project_MOBA/Character/BaseCharacter.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = false;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(FName("Root Component"));
	SetRootComponent(CollisionComponent);
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh Component"));
	MeshComponent->SetupAttachment(GetRootComponent());
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CollisionComponent) CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnProjectileOverlap);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	TimerManager = &GetWorld()->GetTimerManager();
	TimerManager->SetTimer(AutoDestroyTimerHandle, this, &ThisClass::OnDestroyTimerCallback, 5);
	
	if (BulletParticle)
	{
		MainParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(BulletParticle, GetRootComponent(), NAME_None, FVector(ForceInit), FRotator::ZeroRotator, GetActorScale() * FVector::One() * BulletParticleMultiply	);
		if (MainParticleSystemComponent) MainParticleSystemComponent->SetWorldScale3D(FVector::One() * BulletParticleMultiply);
	}
	for (auto& Particle : OpeningParticles)
	{
		if (IsValid(Particle))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(), bShouldRotateOpeningParticle ? GetActorRotation() : FVector::Zero().Rotation(), GetActorScale() * FVector::One() * OpeningParticleMultiply);
		}
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner) return;
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (HasAuthority() && TargetASC) TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);

	if (bShouldDestroyOnOver)
	{
		const bool bCharacter = Cast<ABaseCharacter>(OtherActor) != nullptr;
		if (bCharacter && HitCharacterParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitCharacterParticle, SweepResult.ImpactPoint, FRotator::ZeroRotator, GetActorScale() * FVector::One() * HitParticleMultiply);
		}
		else if (HitWorldParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldParticle, SweepResult.ImpactPoint, FRotator::ZeroRotator, GetActorScale() * FVector::One() * HitParticleMultiply);
		}
		Destroy();
	}
}

void AProjectile::SetSpecHandle(const FGameplayEffectSpecHandle& InSpecHandle)
{
	EffectSpecHandle = InSpecHandle;
}

void AProjectile::OnDestroyTimerCallback()
{
	Destroy();
}
void AProjectile::Destroyed()
{
	if (CollisionComponent) CollisionComponent->OnComponentBeginOverlap.Clear();
	TimerManager->ClearTimer(AutoDestroyTimerHandle);
	Super::Destroyed();
}




