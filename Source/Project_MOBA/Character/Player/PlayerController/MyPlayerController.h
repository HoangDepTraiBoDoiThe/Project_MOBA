// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class IAttackableInterface;
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

	void HighlightingActor();
	
	void OnInputPressed(FGameplayTag InputTag);
	void OnInputHeld(FGameplayTag InputTag);
	void OnInputReleased(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> RMB;
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> CursorTraceObjectTypes;
	
private:
	void bShouldHighlight(IAttackableInterface* Actor, bool b) const;
	
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> IMC;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Q;

	TObjectPtr<AMyPlayerState> MyPlayerState;

	bool bShouldAutoRunToLocation = false;
	FVector DestinyLocation;

	// Highlighting
	IAttackableInterface* CurrentTargetActorUnderMouse;
	IAttackableInterface* PreviousTargetActorUnderMouse;
};
