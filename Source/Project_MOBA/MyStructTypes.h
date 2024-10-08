
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MyStructTypes.generated.h"

/**
 * 
 */

class UBaseGameplayAbility;
class UGameplayEffect;
class UGameplayAbility;

USTRUCT(BlueprintType)
struct FCharacterAbilityStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	bool ShouldGiveAbilityOnStart = false;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseGameplayAbility> Ability = nullptr;
};

USTRUCT(BlueprintType)
struct FCharacterSpecificInfosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CharacterTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultGE_PrimaryAttributeValues = TSubclassOf<UGameplayEffect>(); 
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FCharacterAbilityStruct> CharacterAbilities = TArray<FCharacterAbilityStruct>();

	UPROPERTY(EditDefaultsOnly, Category="Animation montages")
	TMap<FGameplayTag, TObjectPtr<UAnimMontage>> CharacterMontages = TMap<FGameplayTag, TObjectPtr<UAnimMontage>>();

	UPROPERTY(EditDefaultsOnly, Category="Particles")
	TArray<TObjectPtr<UParticleSystem>> DieParticleSystems = TArray<TObjectPtr<UParticleSystem>>();
};
USTRUCT(BlueprintType)
struct FRewardForPlayerStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 XPRequireForTheNextLevel = 0;
};

USTRUCT(BlueprintType)
struct FCharacterInfosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FCharacterSpecificInfosStruct> CharacterSpecificInfosStructs = TArray<FCharacterSpecificInfosStruct>();
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UBaseGameplayAbility>> PassiveAbilitiesClasses = TArray<TSubclassOf<UBaseGameplayAbility>>();
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> DefaultGEs_SecondaryAttributeValues = TArray<TSubclassOf<UGameplayEffect>>();

	UPROPERTY(EditDefaultsOnly)
	TArray<FRewardForPlayerStruct> RewardsForPlayerStructs = TArray<FRewardForPlayerStruct>();
};

UCLASS()
class PROJECT_MOBA_API UMyStructTypes : public UObject
{
	GENERATED_BODY()

public:

protected:

private:
	
};
