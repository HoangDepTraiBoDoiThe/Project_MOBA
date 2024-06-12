// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

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
	virtual void Tick(float DeltaSeconds) override;
	FORCEINLINE APlayerCharacter* GetPlayerCharacter();
	AMyPlayerState* GetMyPlayerState();
	virtual void AcknowledgePossession(APawn* P) override;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	void CharacterMoveToLocation();

	void OnInputPressed(FGameplayTag AbilityTag);
	void OnInputHeld(FGameplayTag AbilityTag);
	void OnInputReleased(FGameplayTag AbilityTag);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RMB;
	
private:
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Q;

	TObjectPtr<AMyPlayerState> MyPlayerState;

	bool bShouldAutoRunToLocation = false;
	FVector LocationToMove;
	
};
