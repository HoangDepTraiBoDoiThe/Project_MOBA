// Fill out your copyright notice in the Description page of Project Settings.

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
	TMap<TObjectPtr<UInputAction>, FGameplayTag> InputActionInfos = TMap<TObjectPtr<UInputAction>, FGameplayTag>();

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};

UCLASS()
class PROJECT_MOBA_API UMyStructTypes : public UObject
{
	GENERATED_BODY()

public:

protected:

private:
	
};
