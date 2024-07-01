// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectAbility.h"
#include "ProjectileEffectAbility.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UProjectileEffectAbility : public UGameplayEffectAbility
{
	GENERATED_BODY()

public:
	UProjectileEffectAbility();

	UFUNCTION(BlueprintCallable)
	AProjectile* SpawnProjectileAtSocket(FVector TargetLocation, bool bIgnorePitch, FName SocketName = "Muzzle", FVector ProjectileScale = FVector(1, 1, 1), bool bMoving = false, const float ProjectileSpeed = 0);
	UFUNCTION(BlueprintCallable)
	AProjectile* SpawnProjectileAtSelectedLocation(FVector TargetLocation, bool bIgnorePitch, FVector SpawnLocation, FVector ProjectileScale = FVector(1, 1, 1), bool bMoving = false, const float ProjectileSpeed = 0);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> EffectClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileClassToSpawn;
	
private:
	
};
