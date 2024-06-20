// Cu Nhat Hoang

#include "ProjectileAbility.h"

#include "AbilitySystemComponent.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"
#include "SpawnActor/Projectile.h"

UProjectileAbility::UProjectileAbility()
{
}

FGameplayEffectSpecHandle UProjectileAbility::MakeGameplayEffect()
{
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, 1, ContextHandle);

	SpecHandle.Data.Get()->SetSetByCallerMagnitude(MyGameplayTagsManager::Get().DamageType_Elemental_Fire, 10);
	return SpecHandle;
}

void UProjectileAbility::SpawnProjectile(const FVector& TargetLocation)
{
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileToSpawn, FTransform(), GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()));
	
	FTransform ProjectileTransform;
	FVector Direction = (TargetLocation - GetAvatarActorFromActorInfo()->GetActorLocation()).GetSafeNormal2D(0);
	ProjectileTransform.SetRotation(Direction.Rotation().Quaternion());
	ProjectileTransform.SetLocation(GetAvatarActorFromActorInfo()->GetActorLocation());
	Projectile->SetSpecHandle(MakeGameplayEffect().Data);
	
	Projectile->FinishSpawning(ProjectileTransform);
}
