// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "MyAbilitySystemComponent.generated.h"

class UBaseGameplayAbility;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAttributevalueBroadcastToControllerSignature, const FOnAttributeChangeData&)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGameplayAbilityStatusToControllerSignature, const FGameplayTag AbilityTag, const FGameplayTag UnlockState, int32 AbilityLevel)

UCLASS()
class PROJECT_MOBA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	//TODO: This could be used for other actors that implementing this ASC, not just BasePlayerCharacter. 
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// For tags in Ability's tag.
	bool TryActivateAbilityByTag(const FGameplayTag AbilityTag);
	void ReceiveAndBindCallBackToDependencies();
	/*
	 Give abilities, default attribute values, bind callback functions and etc to character.
	 */
	void ActorASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor);

	FGameplayTagContainer GetLevelUpAbleAbilityTags(const int32 CharacterLevel);
	bool UnlockAbility(FGameplayTag AbilityTag);
	bool AbilityLeveling(FGameplayTag AbilityTag, int32 CharacterLevel);
	UFUNCTION(Server, Reliable)
	void Server_LevelUpAbility(const FGameplayTag AbilityTag, const int32 CharacterLevel);
	UFUNCTION(Client, Reliable)
	void ClientBroadCastAbilityStateUpdated(const FGameplayTag AbilityTag, const FGameplayTag UnlockState, int32 AbilityLevel);
	void BroadCastActivatableAbilityUIData();
	FGameplayTag GetAbilityUnlockStateByAbilitySpec(const FGameplayAbilitySpec& AbilitySpec);

	FGameplayAttributevalueBroadcastToControllerSignature OnNewAttributeValueBroadcastToControllerDelegate;
	FGameplayAbilityStatusToControllerSignature OnGameplayAbilityStatusToControllerDelegate;

protected:
	void ApplyDefaultGEs();
	void GiveStartupAbilities();

private:
	UPROPERTY()
	TObjectPtr<ABaseCharacter> BaseCharacter;
	UPROPERTY(Replicated)
	FGameplayTagContainer UnlockAbleAbilityTags;

	ABaseCharacter* GetBaseCharacter();
};
