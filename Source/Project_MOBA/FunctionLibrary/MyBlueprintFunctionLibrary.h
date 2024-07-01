// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

class UGameplayEffect;
class AAreaOfEffectActor;
struct FGameplayEffectSpecHandle;
class UAbilitySystemComponent;
class AProjectile;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void GetFilteredActorListFromComponentList(const UObject* WorldContextObject, const FVector SpherePos,
														 float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass* InterfaceClassFilter,
														 const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors);

	UFUNCTION(BlueprintCallable, Category=Spawning)
	static AProjectile* SpawnProjectile(const UObject* WorldContextObject, TSubclassOf<AProjectile> ProjectileToSpawn, const FGameplayEffectSpecHandle& EffectSpecHandle, FVector SpawnLocation, const FVector& TargetLocation, FVector ProjectileScale, AActor* Owner = nullptr, APawn* Instigator = nullptr, bool bMoving = false, const float ActorInitialSpeed = 0);
	UFUNCTION(BlueprintCallable)
	static FGameplayEffectSpecHandle MakeMyGameplayEffectSpecHandle(const UAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect> EffectClass, int32 EffectLevel = 1);

private:
};
