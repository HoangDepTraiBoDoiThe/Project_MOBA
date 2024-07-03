// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterInfosDataAsset.h"

const TArray<FCharacterSpecificInfosStruct>* UCharacterInfosDataAsset::GetCharacterSpecificInfosStructs() const
{
	return &CharacterInfosStruct.CharacterSpecificInfosStructs;
}
void UCharacterInfosDataAsset::GetStartupAbilities(const FGameplayTag& CharacterTag, TArray<TSubclassOf<UGameplayAbility>>& OutStartupAbilities)
{
	for (auto& Pair : CharacterInfosStruct.CharacterSpecificInfosStructs)
	{
		if (!Pair.CharacterTag.MatchesTagExact(CharacterTag)) continue;
		OutStartupAbilities = Pair.StartupAbilities;
	}
}

TArray<TSubclassOf<UBaseGameplayAbility>>& UCharacterInfosDataAsset::GetPassiveAbilities()
{
	return CharacterInfosStruct.PassiveAbilitiesClasses;
}

void UCharacterInfosDataAsset::GetDefaultGEs(const FGameplayTag& CharacterTag, TSubclassOf<UGameplayEffect>& PrimaryGE,
                                             TArray<TSubclassOf<UGameplayEffect>>& SecondaryGEs)
{
	SecondaryGEs = CharacterInfosStruct.DefaultGEs_SecondaryAttributeValues;
	for (auto& Pair : CharacterInfosStruct.CharacterSpecificInfosStructs)
	{
		if (!Pair.CharacterTag.MatchesTagExact(CharacterTag)) continue;
		PrimaryGE = Pair.DefaultGE_PrimaryAttributeValues;
		return;
	}
}

void UCharacterInfosDataAsset::GetParticleSystems(const FGameplayTag& CharacterTag, TArray<TObjectPtr<UParticleSystem>>& OutParticleSystems)
{
	for (auto& Pair : CharacterInfosStruct.CharacterSpecificInfosStructs)
	{
		if (!Pair.CharacterTag.MatchesTagExact(CharacterTag)) continue;
		OutParticleSystems = Pair.DieParticleSystems;
	}
}
