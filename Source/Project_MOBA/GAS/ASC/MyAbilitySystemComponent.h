// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "MyAbilitySystemComponent.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAttributevalueBroadcastToControllerSignature, const FOnAttributeChangeData&)
DECLARE_MULTICAST_DELEGATE_TwoParams(FGameplayAbilityStatusToControllerSignature, const FGameplayTag AbilityTag, const FGameplayTag UnlockState)

UCLASS()
class PROJECT_MOBA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//TODO: This could be used for other actors that implementing this ASC, not just BasePlayerCharacter. 
	
public:
	// For tags in Ability's tag.
	bool TryActivateAbilityByTag(const FGameplayTag AbilityTag);
	void ReceiveAndBindCallBackToDependencies();
	/*
	 Give abilities, default attribute values, bind callback functions and etc to character.
	 */
	void ActorASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor);
	FGameplayTagContainer GetLevelUpAbleAbilityTags(const int32 CharacterLevel);
	UFUNCTION(Server, Reliable)
	void Server_LevelUpAbility(const FGameplayTag AbilityTag, const int32 CharacterLevel);
	void BroadCastActivatableAbilityUIData();
	FGameplayTag GetAbilityUnlockStateByAbilitySpec(const FGameplayAbilitySpec& AbilitySpec);

	FGameplayAttributevalueBroadcastToControllerSignature OnNewAttributeValueBroadcastToControllerDelegate;
	FGameplayAbilityStatusToControllerSignature OnGameplayAbilityStatusToControllerDelegate;

protected:
	void ApplyDefaultGEs();
	void GiveStartupAbilities();
	UFUNCTION(Client, Reliable)
	void ClientOnAbilityStatusChange(FGameplayTag AbilityTag, FGameplayTag AbilityState);

private:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> BaseCharacter;

	ABaseCharacter* GetBaseCharacter();
};
