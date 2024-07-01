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
	TArray<TSubclassOf<UGameplayAbility>>* GetStartupAbilities(const FGameplayTag& CharacterTag);
	void GetDefaultGEs(const FGameplayTag& CharacterTag, TSubclassOf<UGameplayEffect>& PrimaryGE, TArray<TSubclassOf<UGameplayEffect>>& SecondaryGEs);

protected:
	UPROPERTY(EditAnywhere)
	FCharacterInfosStruct CharacterInfosStruct;

private:
	
};
