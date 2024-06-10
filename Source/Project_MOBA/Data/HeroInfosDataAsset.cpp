// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroInfosDataAsset.h"

TMap<TObjectPtr<UInputAction>, FGameplayTag>* UHeroInfosDataAsset::GetInputActionInfos(const FGameplayTag& HeroTag)
{
	for (auto& [HeroTag, InputActionInfos] : HeroInfosStructs)
	{
		if (HeroTag.MatchesTagExact(HeroTag))
		{
			return &InputActionInfos;
		}
	}
	return nullptr;
}
