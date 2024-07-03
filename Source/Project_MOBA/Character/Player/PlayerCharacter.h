// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

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
	const TMap<TObjectPtr<UInputAction>, FGameplayTag>* GetHeroInputActionInfos() const;

	AMyPlayerState* GetMyPlayerState();
	AMyPlayerController* GetMyPlayerController();

	// ICombatInterface override funcions.
	virtual int32 GetXP() override;
	virtual int32 GetXPReward() override;
	virtual void IncreaseXP2Give(const int32 XPAmount) override;

	int32 GetCharacterLevel();

protected:
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


	TObjectPtr<AMyPlayerState> MyPlayerState;
	TObjectPtr<AMyPlayerController> MyPlayerController;
	
private:
	
};
