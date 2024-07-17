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

	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
	}
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetupDestroyTimer();
}

void AProjectile::SetupParticles(const FVector& SpawnLocation)
{
	if (BulletParticle)
	{
		MainParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(BulletParticle, GetRootComponent(), NAME_None, FVector(ForceInit), FRotator::ZeroRotator, GetActorScale() * FVector::One() * BulletParticleMultiply);
		if (MainParticleSystemComponent) MainParticleSystemComponent->SetWorldScale3D(FVector::One() * BulletParticleMultiply);
	}
	for (auto& Particle : OpeningParticles)
	{
		if (IsValid(Particle))
		{
			FVector DecideSpawnLocation = SpawnLocation.IsZero() ? GetActorLocation() : SpawnLocation;
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, DecideSpawnLocation, bShouldRotateOpeningParticle ? GetActorRotation() : FVector::Zero().Rotation(), GetActorScale() * FVector::One() * OpeningParticleMultiply);
		}
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetupDestroyTimer()
{
	TimerManager = &GetWorld()->GetTimerManager();
	TimerManager->SetTimer(AutoDestroyTimerHandle, this, &ThisClass::OnDestroyTimerCallBack, 5);
}

void AProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Owner || !HasAuthority()) return;
	ICombatInterface* OverlappedCombatActor = Cast<ICombatInterface>(OtherActor);
	if (!OverlappedCombatActor) return;
	const bool IsTheSameTeam = Cast<ICombatInterface>(GetInstigator())->GetTeamTag().MatchesTagExact(OverlappedCombatActor->GetTeamTag());
	if (IsTheSameTeam) return;
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetASC)
	{
		FActiveGameplayEffectHandle Handle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
		TargetsOnArea.Add(TargetASC, Handle);
	}

	if (bShouldDestroyOnOver)
	{
		const bool bCharacter = Cast<ABaseCharacter>(OtherActor) != nullptr;
		const bool bZeroImpactPointVector = SweepResult.ImpactPoint.IsZero();
		const FVector SpawnLocation = !bZeroImpactPointVector ? FVector(SweepResult.ImpactPoint) : GetActorLocation();
		if (bCharacter && HitCharacterParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitCharacterParticle, SpawnLocation, FRotator::ZeroRotator, GetActorScale() * FVector::One() * HitParticleMultiply);
		}
		else if (HitWorldParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldParticle, SpawnLocation, FRotator::ZeroRotator, GetActorScale() * FVector::One() * HitParticleMultiply);
		}
		Destroy();
	}
}

void AProjectile::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bool isCombatActor = OtherActor->Implements<UCombatInterface>();
	if (OtherActor == Owner || !HasAuthority() || !isCombatActor) return;
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetASC && !TargetsOnArea.IsEmpty())
	{
		FActiveGameplayEffectHandle ActiveGameplayEffectHandle;
		if (TargetsOnArea.RemoveAndCopyValue(TargetASC, ActiveGameplayEffectHandle))
		{
			TargetASC->RemoveActiveGameplayEffect(ActiveGameplayEffectHandle);
			
		}
	}
}

void AProjectile::SetSpecHandle(const FGameplayEffectSpecHandle& InSpecHandle)
{
	EffectSpecHandle = InSpecHandle;
}

void AProjectile::OnDestroyTimerCallBack()
{
	Destroy();
}

void AProjectile::RemoveEffectAllTargetsOnArea()
{
	if (!HasAuthority()) return;
	for (const auto& Pair : TargetsOnArea)
	{
		Pair.Key->RemoveActiveGameplayEffect(Pair.Value);
	}
	TargetsOnArea.Empty();
}

void AProjectile::Destroyed()
{
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.Clear();
		CollisionComponent->OnComponentEndOverlap.Clear();
	}
	RemoveEffectAllTargetsOnArea();
	TimerManager->ClearTimer(AutoDestroyTimerHandle);
	Super::Destroyed();
}




