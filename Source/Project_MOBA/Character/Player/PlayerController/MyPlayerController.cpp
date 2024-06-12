// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "MyEnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Data/HeroInfosDataAsset.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	const FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bShouldAutoRunToLocation)
	{
		const FVector MoveDirection = (LocationToMove - GetPlayerCharacter()->GetActorLocation()).GetSafeNormal();
		GetPlayerCharacter()->AddMovementInput(MoveDirection);
		float Range = FMath::Abs((GetCharacter()->GetActorLocation() - LocationToMove).Size2D());
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%f"), Range));
		if (Range <= 50.f) bShouldAutoRunToLocation = false;
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
}

void AMyPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);
	
	if (UMyEnhancedInputComponent* EnhancedInputComponent = Cast<UMyEnhancedInputComponent>(InputComponent))
	{
		if (!GetPlayerCharacter()) return;
		TMap<TObjectPtr<UInputAction>, FGameplayTag>* InputInfos = PlayerCharacter->GetHeroInfosDataAsset()->GetInputActionInfos(PlayerCharacter->GetHeroTag());
		EnhancedInputComponent->SetupInputActions(*InputInfos, this, &ThisClass::OnInputPressed, &ThisClass::OnInputHeld, &ThisClass::OnInputReleased);
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(IMC, 0);
}

void AMyPlayerController::CharacterMoveToLocation()
{
	FHitResult Out_MouseLocation;
	GetHitResultUnderCursor(ECC_Visibility, false, Out_MouseLocation);
	LocationToMove = Out_MouseLocation.ImpactPoint;
	bShouldAutoRunToLocation = true;
	
	DrawDebugSphere(GetWorld(), LocationToMove, 15.f, 12, FColor::Green, false, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(), GetPlayerCharacter()->GetActorLocation(), LocationToMove, 5.f, FLinearColor::Green, 5.f);
}

void AMyPlayerController::OnInputPressed(FGameplayTag AbilityTag)
{
	if (AbilityTag.MatchesTagExact(MyGameplayTagsManager::Get().Control_RMB))
	{
		CharacterMoveToLocation();
	}
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

