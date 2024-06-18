// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "MyEnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Data/HeroInfosDataAsset.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

AMyPlayerController::AMyPlayerController()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("Spline component"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetShowMouseCursor(true);
	SetInputMode(InputModeGameAndUI);

}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CharacterAutoMovetoLocation();
	HighlightingActor();
}

void AMyPlayerController::HighlightingActor()
{
	if (!IsLocalController()) return;
	FHitResult HitResult;
	GetHitResultUnderCursorForObjects(CursorTraceObjectTypes, false, HitResult);

	PreviousTargetActorUnderMouse = CurrentTargetActorUnderMouse;
	if (HitResult.bBlockingHit)
		CurrentTargetActorUnderMouse = Cast<IAttackableInterface>(HitResult.GetActor());
	else CurrentTargetActorUnderMouse = nullptr;

	if (CurrentTargetActorUnderMouse && Cast<APlayerCharacter>(HitResult.GetActor()) != GetPlayerCharacter())
	{
		bShouldHighlight(CurrentTargetActorUnderMouse, true);
		if (PreviousTargetActorUnderMouse && PreviousTargetActorUnderMouse != CurrentTargetActorUnderMouse)
			bShouldHighlight(PreviousTargetActorUnderMouse, false);
	}
	else
	{
		if (PreviousTargetActorUnderMouse)
			bShouldHighlight(PreviousTargetActorUnderMouse, false);
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
	DestinyLocation = Out_MouseLocation.ImpactPoint;

	UNavigationPath* NavigationPathToLocation = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), GetCharacterLocation(), DestinyLocation);
	if (NavigationPathToLocation)
	{
		NavigationPathToLocation->EnableRecalculationOnInvalidation(ENavigationOptionFlag::Enable);
		NavigationPathToLocation->EnableDebugDrawing(true, FLinearColor::Blue);
		SplineComponent->ClearSplinePoints();
		SplineComponent->SetSplineWorldPoints(NavigationPathToLocation->PathPoints);
	}

	bShouldAutoRunToLocation = true;
}

void AMyPlayerController::CharacterAutoMovetoLocation()
{
	if (bShouldAutoRunToLocation)
	{
		const FVector MoveDirection = SplineComponent->FindDirectionClosestToWorldLocation(GetCharacterLocation(), ESplineCoordinateSpace::World);
		GetPlayerCharacter()->AddMovementInput(MoveDirection);
		const FVector LocationClosestToCharacter = SplineComponent->FindLocationClosestToWorldLocation(GetCharacterLocation(), ESplineCoordinateSpace::World);
		const float DistanceToDestination = FMath::Abs((LocationClosestToCharacter - DestinyLocation).Size2D());
		if (DistanceToDestination <= 50.f)
			bShouldAutoRunToLocation = false;
	}
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

void AMyPlayerController::bShouldHighlight(IAttackableInterface* Actor, bool b) const
{
	if (!Actor) return;
	Actor->GetAttackableActorMesh()->bRenderCustomDepth = b;
	Actor->GetAttackableActorMesh()->SetCustomDepthStencilValue((b) ? 250 : 0);
	Actor->GetAttackableActorMesh()->MarkRenderStateDirty();
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

FVector AMyPlayerController::GetCharacterLocation()
{
	return GetPlayerCharacter()->GetActorLocation();
}
