// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroInfosDataAsset.h"

TMap<TObjectPtr<UInputAction>, FGameplayTag>* UHeroInfosDataAsset::GetInputActionInfos(const FGameplayTag& HeroTag)
{
	for (auto& HeroInfo : HeroInfosStructs)
	{
		if (HeroTag.MatchesTagExact(HeroTag))
		{
			return &HeroInfo.InputActionInfos;
		}
	}
	return nullptr;
}

TArray<TSubclassOf<UGameplayAbility>>* UHeroInfosDataAsset::GetStartupAbilities(const FGameplayTag& HeroTag)
{
	for (auto& HeroInfo : HeroInfosStructs)
	{
		if (HeroTag.MatchesTagExact(HeroTag))
		{
			return &HeroInfo.StartupAbilities;
		}
	}
	return nullptr;
}
