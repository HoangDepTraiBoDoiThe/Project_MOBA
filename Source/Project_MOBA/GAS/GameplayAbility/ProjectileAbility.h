// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "DamageAbility.h"
#include "ProjectileAbility.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UProjectileAbility : public UDamageAbility
{
	GENERATED_BODY()

public:
	UProjectileAbility();

	UFUNCTION(BlueprintCallable)
	FGameplayEffectSpecHandle MakeGameplayEffect();
	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation, FName SocketLocation = "PuzzleSocket", FVector ProjectileScale = FVector(1, 1, 1));

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> Effect;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileToSpawn;
	
private:
	
};
