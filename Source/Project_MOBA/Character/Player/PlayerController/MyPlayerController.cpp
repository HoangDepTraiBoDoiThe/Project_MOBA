// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "MyEnhancedInputComponent.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/Data/HeroInfosDataAsset.h"

AMyPlayerController::AMyPlayerController()
{
	
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
 	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(IMC, 0);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UMyEnhancedInputComponent* EnhancedInputComponent = Cast<UMyEnhancedInputComponent>(InputComponent))
	{
		if (!GetPlayerCharacter()) return;
		TMap<TObjectPtr<UInputAction>, FGameplayTag>* InputInfos = PlayerCharacter->GetHeroInfosDataAsset()->GetInputActionInfos(PlayerCharacter->GetHeroTag());
		EnhancedInputComponent->SetupInputActions(*InputInfos, this, &ThisClass::OnInputPressed, &ThisClass::OnInputHeld, &ThisClass::OnInputReleased);
	}
}

void AMyPlayerController::OnInputPressed(FGameplayTag AbilityTag)
{
}

void AMyPlayerController::OnInputHeld(FGameplayTag AbilityTag)
{
}

void AMyPlayerController::OnInputReleased(FGameplayTag AbilityTag)
{
}

APlayerCharacter* AMyPlayerController::GetPlayerCharacter()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	}
	return PlayerCharacter;
}

AMyPlayerState* AMyPlayerController::GetMyPlayerState()
{
	if (!MyPlayerState) MyPlayerState = GetPlayerCharacter()->GetMyPlayerState();
	return MyPlayerState;
}
