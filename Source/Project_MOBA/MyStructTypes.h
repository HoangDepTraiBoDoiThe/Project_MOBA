
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MyStructTypes.generated.h"

/**
 * 
 */

class UGameplayEffect;
class UGameplayAbility;

USTRUCT(BlueprintType)
struct FCharacterSpecificInfosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CharacterTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultGE_PrimaryAttributeValues; 
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};

USTRUCT(BlueprintType)
struct FCharacterInfosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FCharacterSpecificInfosStruct> CharacterInfosStructs;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> DefaultGEs_SecondaryAttributeValues;
};

UCLASS()
class PROJECT_MOBA_API UMyStructTypes : public UObject
{
	GENERATED_BODY()

public:

protected:

private:
	
};
