// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInfosDataAsset.h"

const TArray<FCharacterSpecificInfosStruct>* UCharacterInfosDataAsset::GetCharacterSpecificInfosStructs() const
{
	return &CharacterInfosStruct.CharacterInfosStructs;
}
TArray<TSubclassOf<UGameplayAbility>>* UCharacterInfosDataAsset::GetStartupAbilities(const FGameplayTag& CharacterTag)
{
	for (auto& Pair : CharacterInfosStruct.CharacterInfosStructs)
	{
		if (!Pair.CharacterTag.MatchesTagExact(CharacterTag)) continue;
		return &Pair.StartupAbilities;
	}
	return nullptr;
}

void UCharacterInfosDataAsset::GetDefaultGEs(const FGameplayTag& CharacterTag, TSubclassOf<UGameplayEffect>& PrimaryGE,
	TArray<TSubclassOf<UGameplayEffect>>& SecondaryGEs)
{
	SecondaryGEs = CharacterInfosStruct.DefaultGEs_SecondaryAttributeValues;
	for (auto& Pair : CharacterInfosStruct.CharacterInfosStructs)
	{
		if (!Pair.CharacterTag.MatchesTagExact(CharacterTag)) continue;
		PrimaryGE = Pair.DefaultGE_PrimaryAttributeValues;
		return;
	}
}
