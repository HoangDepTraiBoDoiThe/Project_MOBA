// Cu Nhat Hoang


#include "Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Project_MOBA/Character/BaseCharacter.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
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
	TimerManager->SetTimer(AutoDestroyTimerHandle, this, &ThisClass::OneDestroyTimerCallback, 10);
	
	SetReplicateMovement(true);
	if (BulletParticle) UGameplayStatics::SpawnEmitterAttached(BulletParticle, GetRootComponent())->SetWorldScale3D(FVector::One() * BulletParticleMultiply);
	for (auto& Particle : OpeningParticles)
	{
		if (Particle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation(),
			                                         bShouldRotateOpeningParticle
				                                         ? GetActorRotation()
				                                         : FVector::Zero().Rotation(),
			                                         GetActorScale())->SetWorldScale3D(
				FVector::One() * OpeningParticleMultiply);
		}
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnProjectileOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner) return;
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (HasAuthority() && TargetASC) TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Get());

	if (bShouldDestroyOnOver)
	{
		const bool bCharacter = Cast<ABaseCharacter>(OtherActor) != nullptr;
		if (bCharacter && HitCharacterParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitCharacterParticle, SweepResult.ImpactPoint)->SetWorldScale3D(FVector::One() * HitParticleMultiply);
		}
		else if (HitWorldParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldParticle, SweepResult.ImpactPoint)->SetWorldScale3D(FVector::One() * HitParticleMultiply);
		}
		Destroy();
	}
}

void AProjectile::SetSpecHandle(const TSharedPtr<FGameplayEffectSpec>& InSpec)
{
	EffectSpec = InSpec;
}

void AProjectile::OneDestroyTimerCallback()
{
	Destroy();
}
void AProjectile::Destroyed()
{
	if (CollisionComponent) CollisionComponent->OnComponentBeginOverlap.Clear();
	TimerManager->ClearTimer(AutoDestroyTimerHandle);
	Super::Destroyed();
}




