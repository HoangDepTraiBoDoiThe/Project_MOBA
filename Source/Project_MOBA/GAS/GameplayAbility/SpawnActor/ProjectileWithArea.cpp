// Cu Nhat Hoang


#include "ProjectileWithArea.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Project_MOBA/Character/BaseCharacter.h"

AProjectileWithArea::AProjectileWithArea()
{
	AreaCollision = CreateDefaultSubobject<UCapsuleComponent>("AreaCollision");
	AreaCollision->SetupAttachment(GetRootComponent());
}

void AProjectileWithArea::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		AreaCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAreaOverlap);
		AreaCollision->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnAreaEndOverlap);
	}
}

void AProjectileWithArea::SpawnArea()
{

}

void AProjectileWithArea::OnAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool isCombatActor = OtherActor->Implements<UCombatInterface>();
	if (OtherActor == Owner || !HasAuthority() || !isCombatActor) return;
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
		TargetsOnArea.Add(TargetASC);
	}
}

void AProjectileWithArea::OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bool isCombatActor = OtherActor->Implements<UCombatInterface>();
	if (OtherActor == Owner || !HasAuthority() || !isCombatActor) return;
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		TargetsOnArea.Remove(TargetASC);
		TargetASC->RemoveActiveEffectsWithTags(FGameplayTagContainer(AbilityTag));
	}
}

void AProjectileWithArea::RemoveEffectAllTargetsOnArea()
{
	if (!HasAuthority()) return;
	for (auto TargetASC : TargetsOnArea)
	{
		TargetASC->RemoveActiveEffectsWithTags(FGameplayTagContainer(AbilityTag));
	}
}

void AProjectileWithArea::OnEnding()
{
	RemoveEffectAllTargetsOnArea();
	SetLifeSpan(1.f);
}

