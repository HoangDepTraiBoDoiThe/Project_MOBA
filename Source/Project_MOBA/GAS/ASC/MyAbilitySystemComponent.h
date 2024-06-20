// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	bool TryActivateAbilityByInputTag(const FGameplayTag InputTag);

	/*
	 *Give abilities, default effects, etc to player
	 */
	void PlayerASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor);

protected:

private:

	
};
