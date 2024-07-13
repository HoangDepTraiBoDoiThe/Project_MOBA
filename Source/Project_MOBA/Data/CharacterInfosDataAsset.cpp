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

TObjectPtr<UAnimMontage> UCharacterInfosDataAsset::GetMontageByTag(const FGameplayTag& CharacterTag, const FGameplayTag& MontageTag)
{
	for (auto& Pair : CharacterInfosStruct.CharacterSpecificInfosStructs)
	{
		if (Pair.CharacterTag.MatchesTagExact(CharacterTag))
			return Pair.CharacterMontages.FindRef(MontageTag);
	}
	return nullptr;
}

int32 UCharacterInfosDataAsset::GetLevelAtXP(const int32 XP2Check, const int32 StartCheckAtLevel)
{
	for (int32 i = StartCheckAtLevel; i < CharacterInfosStruct.RewardsForPlayerStructs.Num(); i++)
	{
		if (CharacterInfosStruct.RewardsForPlayerStructs[i].XPRequireForTheNextLevel > XP2Check)
		{
			return i;
		}
	}
	return 18;
}

FRewardForPlayerStruct UCharacterInfosDataAsset::GetRewardStructAtXP(const int32 XP2Check)
{
	for (int32 i = 1; i < CharacterInfosStruct.RewardsForPlayerStructs.Num(); i++)
	{
		if (CharacterInfosStruct.RewardsForPlayerStructs[i].XPRequireForTheNextLevel > XP2Check)
		{
			return CharacterInfosStruct.RewardsForPlayerStructs[i];
		}
	}
	return CharacterInfosStruct.RewardsForPlayerStructs[19];
}

void UCharacterInfosDataAsset::GetXPInfos(const int32 CurrentXP, const int32 OldXP, int32& Loop, int32& XPForCurrentLevel, int32& XPForNextLevel)
{
	int32 OldLevel = 0;
	int32 CurrentLevel = 0;
	for (int32 i = 1; i < CharacterInfosStruct.RewardsForPlayerStructs.Num(); i++)
	{
		if (CharacterInfosStruct.RewardsForPlayerStructs[i].XPRequireForTheNextLevel > OldXP)
		{
			OldLevel = i;
		}
		if (CharacterInfosStruct.RewardsForPlayerStructs[i].XPRequireForTheNextLevel > CurrentXP)
		{
			CurrentLevel = i;
			XPForCurrentLevel = CharacterInfosStruct.RewardsForPlayerStructs[i - 1].XPRequireForTheNextLevel;
			XPForNextLevel = CharacterInfosStruct.RewardsForPlayerStructs[i].XPRequireForTheNextLevel;
			Loop = CurrentLevel - OldLevel;
			return;
		}
	}
}
