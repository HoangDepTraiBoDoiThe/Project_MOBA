
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "MyStructTypes.generated.h"

/**
 * 
 */

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FHeroInfosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HeroTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};

USTRUCT(BlueprintType)
struct FPlayerInfosStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TMap<TObjectPtr<UInputAction>, FGameplayTag> InputActionInfos = TMap<TObjectPtr<UInputAction>, FGameplayTag>();

	UPROPERTY(EditDefaultsOnly)
	TArray<FHeroInfosStruct> HeroInfosStructs;
};

UCLASS()
class PROJECT_MOBA_API UMyStructTypes : public UObject
{
	GENERATED_BODY()

public:

protected:

private:
	
};
