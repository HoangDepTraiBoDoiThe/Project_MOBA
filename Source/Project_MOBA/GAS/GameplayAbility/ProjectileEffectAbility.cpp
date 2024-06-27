// Cu Nhat Hoang

#include "ProjectileEffectAbility.h"

#include "AbilitySystemComponent.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/Interface/CombatInterface.h"

UProjectileEffectAbility::UProjectileEffectAbility()
{
}

AProjectile* UProjectileEffectAbility::SpawnProjectileAtSocket(const FVector& TargetLocation, const bool bIgnorePitch, const FName SocketName, const FVector ProjectileScale, bool bMoving, const float ProjectileSpeed)
{
    if (!GetAvatarActorFromActorInfo()->HasAuthority()) return nullptr;
    const FVector SpawnLocation = Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeaponSocketLocationByName(SocketName);
    const FGameplayEffectSpecHandle EffectSpecHandle = UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(GetAbilitySystemComponentFromActorInfo(), EffectClass);
	return UMyBlueprintFunctionLibrary::SpawnProjectile(GetWorld(), ProjectileClassToSpawn, EffectSpecHandle, SpawnLocation, TargetLocation, ProjectileScale, bIgnorePitch, GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()), bMoving, ProjectileSpeed);
}

AProjectile* UProjectileEffectAbility::SpawnProjectileAtSelectedLocation(const FVector& TargetLocation, const bool bIgnorePitch, const FVector SpawnLocation,
                                                                 const FVector ProjectileScale, bool bMoving, const float ProjectileSpeed)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return nullptr;
	const FGameplayEffectSpecHandle EffectSpecHandle = UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(GetAbilitySystemComponentFromActorInfo(), EffectClass);
	return UMyBlueprintFunctionLibrary::SpawnProjectile(GetWorld(), ProjectileClassToSpawn, EffectSpecHandle, SpawnLocation, TargetLocation, ProjectileScale, bIgnorePitch, GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()), bMoving, ProjectileSpeed);
}
