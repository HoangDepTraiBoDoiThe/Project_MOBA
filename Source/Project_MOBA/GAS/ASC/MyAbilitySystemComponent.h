// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//TODO: This could be used for other actors that implementing this ASC, not just BasePlayerCharacter. 
	
public:
	bool TryActivateAbilityByInputTag(const FGameplayTag InputTag);


	void ReceiveAndBindCallBackToDependencies();
	/*
	 Give abilities, default attribute values, bind callback functions and etc to character.
	 */
	void ActorASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor);

protected:
	void ApplyDefaultGEs();
	void GiveStartupAbilities();
	
private:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> BaseCharacter;

	ABaseCharacter* GetBaseCharacter();
};
