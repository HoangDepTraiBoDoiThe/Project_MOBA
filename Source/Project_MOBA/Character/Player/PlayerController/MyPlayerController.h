// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class USplineComponent;
class AMyPlayerState;
class APlayerCharacter;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();
	virtual void BeginPlay() override;
	void CharacterAutoMovetoLocation();
	virtual void Tick(float DeltaSeconds) override;
	FORCEINLINE APlayerCharacter* GetPlayerCharacter();
	AMyPlayerState* GetMyPlayerState();
	virtual void AcknowledgePossession(APawn* P) override;
	FVector GetCharacterLocation();
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	void CharacterMoveToLocation();

	void OnInputPressed(FGameplayTag AbilityTag);
	void OnInputHeld(FGameplayTag AbilityTag);
	void OnInputReleased(FGameplayTag AbilityTag);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RMB;
	TObjectPtr<USplineComponent> SplineComponent;
	
private:
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Q;

	TObjectPtr<AMyPlayerState> MyPlayerState;

	bool bShouldAutoRunToLocation = false;
	FVector DestinyLocation;
	
};
