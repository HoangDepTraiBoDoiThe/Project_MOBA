// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

class UInputAction;

USTRUCT()
struct FHeroInfosStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HeroTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly)
	TMap<TObjectPtr<UInputAction>, FGameplayTag> InputActionInfos = TMap<TObjectPtr<UInputAction>, FGameplayTag>();

};

