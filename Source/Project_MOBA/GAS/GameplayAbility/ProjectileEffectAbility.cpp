// Cu Nhat Hoang

#include "ProjectileEffectAbility.h"

#include "AbilitySystemComponent.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/Interface/CombatInterface.h"

UProjectileEffectAbility::UProjectileEffectAbility()
{
}

AProjectile* UProjectileEffectAbility::SpawnProjectileAtSocket(FVector TargetLocation, const bool bIgnorePitch, const FName SocketName, const FVector ProjectileScale, bool bMoving, const float ProjectileSpeed)
{
    /*
    if (!GetAvatarActorFromActorInfo()->HasAuthority()) return nullptr;
    */
    const FVector SpawnLocation = Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeaponSocketLocationByName(SocketName);
    FGameplayEffectSpecHandle EffectSpecHandle = UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(GetAbilitySystemComponentFromActorInfo(), EffectClass, GetAbilityLevel());
    for (const auto& Pair : EffectTypeMap)
    {
		EffectSpecHandle.Data->SetSetByCallerMagnitude(Pair.Key, Pair.Value.EffectValue);
    }

    if (bIgnorePitch)
    {
    	/*
    	 * ---------------------------------------------------------------
    	 * Convert current mouse 2D position to World Space 3D position and direction
    	 * ---------------------------------------------------------------
    	 */
    	FVector WorldLocation;
    	FVector WorldDirection;
	    Cast<APlayerCharacter>(GetAvatarActorFromActorInfo())->GetMyPlayerController()->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    	/*DrawDebugLine(GetWorld(), WorldLocation, WorldLocation + WorldDirection * 2000, FColor::Yellow, true, 5);
    	DrawDebugSphere(GetWorld(), WorldLocation, .5f, 6, FColor::Yellow, true, 5.f);*/
		// ---------------------------------------------------------------

    	/*
		* ---------------------------------------------------------------
		* Calculate the length to adjust the TargetLocation height along WorldDirection.
		* ---------------------------------------------------------------
		*/
    	FHitResult HitResult;
    	FVector EndLoc = SpawnLocation + WorldDirection * 2000;
    	GetWorld()->LineTraceSingleByChannel(HitResult, SpawnLocation, EndLoc, ECC_Visibility);

    	float Distance2Adjust = FVector::Dist(SpawnLocation, HitResult.ImpactPoint);
    	TargetLocation -= WorldDirection * Distance2Adjust;

    	/*DrawDebugLine(GetWorld(), SpawnLocation, EndLoc, FColor::Red, true, 5);
    	DrawDebugLine(GetWorld(), SpawnLocation, TargetLocation, FColor::Blue, true, 5);
    	DrawDebugSphere(GetWorld(), TargetLocation, 20.f, 6, FColor::Green, true, 5.f);
    	DrawDebugSphere(GetWorld(), SpawnLocation, 10.f, 6, FColor::Green, true, 5.f);
    	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 6, FColor::Red, true, 5.f);*/
    	// ---------------------------------------------------------------
    }
	
	return UMyBlueprintFunctionLibrary::SpawnProjectile(GetWorld(), ProjectileClassToSpawn, EffectSpecHandle, SpawnLocation, TargetLocation, ProjectileScale, GetAbilityTag(), GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()), bMoving, ProjectileSpeed);
}

AProjectile* UProjectileEffectAbility::SpawnProjectileAtSelectedLocation(FVector TargetLocation, const bool bIgnorePitch, const FVector SpawnLocation,
                                                                 const FVector ProjectileScale, bool bMoving, const float ProjectileSpeed)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return nullptr;
	const FGameplayEffectSpecHandle EffectSpecHandle = UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(GetAbilitySystemComponentFromActorInfo(), EffectClass);
	return UMyBlueprintFunctionLibrary::SpawnProjectile(GetWorld(), ProjectileClassToSpawn, EffectSpecHandle, SpawnLocation, TargetLocation, ProjectileScale, GetAbilityTag(), GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()), bMoving, ProjectileSpeed);
}
