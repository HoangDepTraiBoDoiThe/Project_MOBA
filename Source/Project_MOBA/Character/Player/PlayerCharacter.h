// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class AMyHUD;
class UGameplayEffect;
class UGameplayAbility;
class AMyPlayerController;
class USplineComponent;
class AMyPlayerState;
struct FGameplayTag;
class UCharacterInfosDataAsset;
class UCameraComponent;
class USpringArmComponent;
class UInputAction;

/**
 * 
 */

UCLASS()
class PROJECT_MOBA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// Dependencies
	AMyPlayerState* GetMyPlayerState();
	AMyPlayerController* GetMyPlayerController();
	AMyHUD* GetMyHUD();
	
	// Experience
	const TMap<FName, FGameplayTag>& GetRewardAttributeMap() const {return RewardAttributeMap;}
	TObjectPtr<UCurveTable> GetRewardTable() const {return RewardTable;}
	TSubclassOf<UGameplayEffect> GetRewardGE() const {return RewardGE;}
	FORCEINLINE TObjectPtr<UParticleSystem> GetLevelUpParticleSystem() const {return LevelUpParticleSystem;}
	int32 GetCharacterLevel();
	// Experience subset: ICombatInterface override funcions.
	virtual int32 GetXP() override;
	virtual int32 GetXPReward() override;
	virtual void IncreaseXP2Give(const int32 XPAmount) override;

	// Other
	const TMap<TObjectPtr<UInputAction>, FGameplayTag>* GetHeroInputActionInfos() const;

protected:
	// Components
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraArmComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> CameraRootComponent;

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	void PlayerInitializeGASInfos();
	
	UPROPERTY(EditDefaultsOnly)
	TMap<TObjectPtr<UInputAction>, FGameplayTag> InputActionInfos;

	// Experience 
	UPROPERTY(EditAnywhere)
	TMap<FName, FGameplayTag> RewardAttributeMap;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveTable> RewardTable;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> RewardGE;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> LevelUpParticleSystem;

	// Dependencies
	TObjectPtr<AMyHUD> MyHUD;
	TObjectPtr<AMyPlayerState> MyPlayerState;
	TObjectPtr<AMyPlayerController> MyPlayerController;
	
private:
	
};
