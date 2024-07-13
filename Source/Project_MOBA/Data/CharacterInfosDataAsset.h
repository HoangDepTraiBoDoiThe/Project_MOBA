// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Project_MOBA/MyStructTypes.h"
#include "CharacterInfosDataAsset.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_MOBA_API UCharacterInfosDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<FCharacterSpecificInfosStruct>* GetCharacterSpecificInfosStructs() const;
	FORCEINLINE const FCharacterInfosStruct* GetCharacterInfosStruct() const { return &CharacterInfosStruct; }
	void GetStartupAbilities(const FGameplayTag& CharacterTag, TArray<TSubclassOf<UGameplayAbility>>& OutStartupAbilities);
	TArray<TSubclassOf<UBaseGameplayAbility>>& GetPassiveAbilities();
	void GetDefaultGEs(const FGameplayTag& CharacterTag, TSubclassOf<UGameplayEffect>& PrimaryGE, TArray<TSubclassOf<UGameplayEffect>>& SecondaryGEs);
	void GetParticleSystems(const FGameplayTag& CharacterTag, TArray<TObjectPtr<UParticleSystem>>& OutParticleSystems);
	TObjectPtr<UAnimMontage> GetMontageByTag(const FGameplayTag& CharacterTag, const FGameplayTag& MontageTag);
	int32 GetLevelAtXP(const int32 XP2Check, const int32 StartCheckAtLevel = 1);
	FRewardForPlayerStruct GetRewardStructAtXP(const int32 XP2Check);
	void GetXPInfos(const int32 CurrentXP, const int32 OldXP, int32& Loop, int32& XPForCurrentLevel, int32& XPForNextLevel);

protected:
	UPROPERTY(EditAnywhere)
	FCharacterInfosStruct CharacterInfosStruct;

private:
	
};
