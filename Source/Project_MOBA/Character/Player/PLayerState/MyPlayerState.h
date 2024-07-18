// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

struct FGameplayTag;
struct FRewardForPlayerStruct;
class APlayerCharacter;
class UAbilitySystemComponent;
class UBaseAttributeSet;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnIntPropertyChangeTwoParamSignature, const int32 New, const int32 Old)
DECLARE_DELEGATE_TwoParams(FOnEndingGame, const FGameplayTag TeamWinner, const float TotalTime)

DECLARE_DELEGATE_OneParam(FAbilityPointSignature, int32 CharacterLevel)

UCLASS()
class PROJECT_MOBA_API AMyPlayerState : public APlayerState, public  IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;;
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}

	// Experience
	FORCEINLINE int32 GetXP() const {return XP;}
	FORCEINLINE int32 GetXP2Give() const {return XP2Give;}
	void IncreaseXP(int32 XPAmount);
	void RewardPlayer(int32 XP2Increase = 1);
	void IncreaseXP2Give(int32 XP2GiveAmount);
	int32 GetPlayerLevel() const {return PlayerLevel;}
	void LevelUp(const int32 NewLevel);
	void GiveRewardToPlayer(const int32 LevelAtTotalXP);

	FORCEINLINE APlayerCharacter* GetPlayerCharacter();

	UFUNCTION(Client, Reliable)
	void NotifyEndGame(const FGameplayTag TeamWinner, float TimeInMinute);
	
	// Delegates
	FAbilityPointSignature AbilityPointDelegate;
	FOnIntPropertyChangeTwoParamSignature OnXPChangeDelegate;
	FOnIntPropertyChangeTwoParamSignature OnLevelChangeDelegate;
	FOnEndingGame OnEndingGame;

protected:
	UFUNCTION()
	void RepNotify_XP(const int32 OldValue) const;
	void OnLeveling(const int32 OldValue);
	UFUNCTION()
	void RepNotify_PlayerLevel(const int32 OldValue);
	
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;

	// Experience
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> LevelUpParticle;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=RepNotify_XP)
	int32 XP{1};
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=RepNotify_PlayerLevel)
	int32 PlayerLevel{1};
	int32 XP2Give{1};

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
private:

};
