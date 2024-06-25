// Cu Nhat Hoang


#include "Projectile.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
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

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnProjectileOverlap);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetReplicateMovement(true);
	UGameplayStatics::SpawnEmitterAttached(BulletParticle, GetRootComponent());
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
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<ABaseCharacter>(AttackableActor) ? HitFleshParticle : HitWallParticle, SweepResult.ImpactPoint);
	Destroy();
}

void AProjectile::SetSpecHandle(const TSharedPtr<FGameplayEffectSpec>& InSpec)
{
	EffectSpec = InSpec;
}

void AProjectile::Destroyed()
{
	
	BoxComponent->OnComponentBeginOverlap.Clear();
	Super::Destroyed();
}



