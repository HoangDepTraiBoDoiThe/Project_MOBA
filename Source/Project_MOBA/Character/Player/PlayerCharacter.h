// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USplineComponent;
class AMyPlayerState;
struct FGameplayTag;
class UHeroInfosDataAsset;
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
	FORCEINLINE UHeroInfosDataAsset* GetHeroInfosDataAsset() const {return HeroInfos;}

	FGameplayTag GetHeroTag() const {return HeroTag;}

	AMyPlayerState* GetMyPlayerState();
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraArmComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> CameraRootComponent;

	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	void SetPlayerCharacterGASInfos();

	UPROPERTY(EditDefaultsOnly, Category= "Hero info")
	FGameplayTag HeroTag;
	UPROPERTY(EditDefaultsOnly, Category= "Hero info")
	TObjectPtr<UHeroInfosDataAsset> HeroInfos;

	TObjectPtr<AMyPlayerState> MyPlayerState;
	
private:
	
};
