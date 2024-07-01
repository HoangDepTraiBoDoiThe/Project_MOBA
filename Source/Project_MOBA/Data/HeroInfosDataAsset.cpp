// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroInfosDataAsset.h"

const TArray<FHeroInfosStruct>* UHeroInfosDataAsset::GetHeroInfosStructs() const
{
	return &PlayerInfosStruct.HeroInfosStructs;
}

const TMap<TObjectPtr<UInputAction>, FGameplayTag>* UHeroInfosDataAsset::GetInputActionInfos(const FGameplayTag& HeroTag) const
{
	return &PlayerInfosStruct.InputActionInfos;
}

TArray<TSubclassOf<UGameplayAbility>>* UHeroInfosDataAsset::GetStartupAbilities(const FGameplayTag& HeroTag)
{
	for (auto& Pair : PlayerInfosStruct.HeroInfosStructs)
	{
		if (!Pair.HeroTag.MatchesTagExact(HeroTag)) continue;
		return &Pair.StartupAbilities;
	}
	return nullptr;
}

void UHeroInfosDataAsset::GetDefaultGEs(const FGameplayTag& HeroTag, TSubclassOf<UGameplayEffect>& PrimaryGE,
	TArray<TSubclassOf<UGameplayEffect>>& SecondaryGEs)
{
	for (auto& Pair : PlayerInfosStruct.HeroInfosStructs)
	{
		if (!Pair.HeroTag.MatchesTagExact(HeroTag)) continue;
		PrimaryGE = Pair.DefaultGE_PrimaryAttributeValues;
		SecondaryGEs = Pair.DefaultGEs_SecondaryAttributeValues;
		return;
	}
}
