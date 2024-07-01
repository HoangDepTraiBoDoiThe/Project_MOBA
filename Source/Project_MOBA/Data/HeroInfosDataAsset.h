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
	FORCEINLINE const TArray<FHeroInfosStruct>* GetHeroInfosStructs() const;
	FORCEINLINE const FPlayerInfosStruct* GetPlayerInfosStruct() const { return &PlayerInfosStruct; }
	const TMap<TObjectPtr<UInputAction>, FGameplayTag>* GetInputActionInfos(const FGameplayTag& HeroTag) const;
	TArray<TSubclassOf<UGameplayAbility>>* GetStartupAbilities(const FGameplayTag& HeroTag);
	void GetDefaultGEs(const FGameplayTag& HeroTag, TSubclassOf<UGameplayEffect>& PrimaryGE, TArray<TSubclassOf<UGameplayEffect>>& SecondaryGEs);

protected:
	UPROPERTY(EditAnywhere)
	FPlayerInfosStruct PlayerInfosStruct;

private:
	
};
