// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project_MOBA/MyStructTypes.h"
#include "HeroInfosDataAsset.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_MOBA_API UHeroInfosDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<FHeroInfosStruct>* GetHeroInfosStruct() const { return &HeroInfosStructs; }
	TMap<TObjectPtr<UInputAction>, FGameplayTag>* GetInputActionInfos(const FGameplayTag& HeroTag);
	TArray<TSubclassOf<UGameplayAbility>>* GetStartupAbilities(const FGameplayTag& HeroTag);

protected:
	UPROPERTY(EditAnywhere)
	TArray<FHeroInfosStruct> HeroInfosStructs;

private:
	
};
