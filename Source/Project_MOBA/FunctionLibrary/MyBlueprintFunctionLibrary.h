// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Project_MOBA/GAS/GameplayAbility/GameplayEffectAbility.h"
#include "MyBlueprintFunctionLibrary.generated.h"

struct FGameplayTag;
struct FWidgetControllerStruct;
class UMainWidgetController;
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
	static AProjectile* SpawnProjectile(const UObject* WorldContextObject, TSubclassOf<AProjectile> ProjectileToSpawn, const FGameplayEffectSpecHandle& EffectSpecHandle, FVector SpawnLocation, const FVector& TargetLocation, FVector ProjectileScale, FGameplayTag AbilityTag, AActor* Owner = nullptr, APawn* Instigator = nullptr, bool bMoving = false, const float ActorInitialSpeed = 0);
	UFUNCTION(BlueprintCallable)
	static FGameplayEffectSpecHandle MakeMyGameplayEffectSpecHandle(const UAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect> EffectClass, int32 EffectLevel = 1);

	static FWidgetControllerStruct* MakeWidgetControllerInfos(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf = "WorldContextObject"))
	static UMainWidgetController* GetMainWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static FGameplayEffectSpecHandle MakeEffectSpecHandleWithDamageTypeMap(TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* OwningASC, UGameplayAbility* OwningAbility, TMap<FGameplayTag, FMyEffectTypeStruct> EffectTypeMap);

private:
};
