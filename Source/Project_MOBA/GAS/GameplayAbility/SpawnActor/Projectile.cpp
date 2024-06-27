// Cu Nhat Hoang


#include "Projectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "Project_MOBA/Interface/AttackableInterface.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("UBoxComponent"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("MeshComponent"));
	SetRootComponent(BoxComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (BoxComponent) BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnProjectileOverlap);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

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
	IAttackableInterface* AttackableActor = Cast<IAttackableInterface>(OtherActor);
	if (AttackableActor && OtherActor == Owner) return;
	if (AttackableActor && HasAuthority())
	{
		AttackableActor->ApplyEffectSpecToSelf(*EffectSpec.Get());
	}
	if (HitCharacterParticle && HitCharacterParticle) UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ABaseCharacter>(AttackableActor) ? HitCharacterParticle : HitWorldParticle, SweepResult.ImpactPoint)->SetWorldScale3D(FVector::One() * HitParticleMultiply);;
	Destroy();
}

void AProjectile::SetSpecHandle(const TSharedPtr<FGameplayEffectSpec>& InSpec)
{
	EffectSpec = InSpec;
}

void AProjectile::Destroyed()
{
	if (BoxComponent) BoxComponent->OnComponentBeginOverlap.Clear();
	Super::Destroyed();
}



