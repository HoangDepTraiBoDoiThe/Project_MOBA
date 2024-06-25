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
	for (auto& [HeroTag, StartupAbilities] : PlayerInfosStruct.HeroInfosStructs)
	{
		if (HeroTag.MatchesTagExact(HeroTag))
		{
			return &StartupAbilities;
		}
	}
	return nullptr;
}
