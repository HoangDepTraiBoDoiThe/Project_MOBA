// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/Envir/MyPlayerStart.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void AMyGameModeBase::StartPlay()
{
	Super::StartPlay();
	StartTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
}

APawn* AMyGameModeBase::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	if (!StartSpot)
	{
		StartSpot = ChoosePlayerStart(NewPlayer);
	}

	if (StartSpot)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        
		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, StartSpot->GetActorLocation(), StartSpot->GetActorRotation(), SpawnParams);

		if (NewPawn)
		{
			// Set the team tag for the new pawn here if necessary
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(NewPawn);
			if (PlayerCharacter)
			{
				// You might want to implement logic here to determine the initial team
				// For example, based on the number of players on each team
				PlayerCharacter->GetTeamTag() = DetermineInitialTeam();
			}
		}

		return NewPawn;
	}

	return nullptr;
}

TArray<AActor*> AMyGameModeBase::FindAllPlayerStarts(UWorld* World)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World, AMyPlayerStart::StaticClass(), PlayerStarts);
	return PlayerStarts;
}

AMyPlayerStart* AMyGameModeBase::ChoosePlayerStart(AController* Controller)
{
	TArray<AActor*> AllPlayerStarts = FindAllPlayerStarts(GetWorld());
	TArray<AActor*> ValidStartPoints;

	// Get the team tag of the player
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Controller->GetPawn());
	FGameplayTag PlayerTeamTag;
	if (PlayerCharacter)
	{
		PlayerTeamTag = PlayerCharacter->GetTeamTag();
	}
	else
	{
		// If the player doesn't have a character yet (initial spawn), 
		// you might want to determine their team here
		PlayerTeamTag = DetermineInitialTeam();
	}

	// Filter start points based on team tag
	for (AActor* StartPoint : AllPlayerStarts)
	{
		AMyPlayerStart* MyPlayerStart = Cast<AMyPlayerStart>(StartPoint);
		if (MyPlayerStart->GetTeamTag() == PlayerTeamTag)
		{
			ValidStartPoints.Add(MyPlayerStart);
		}
	}

	// If no valid start points found for the team, use any start point
	if (ValidStartPoints.Num() == 0)
	{
		ValidStartPoints = AllPlayerStarts;
	}

	// Choose a random start point from the valid ones
	if (ValidStartPoints.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, ValidStartPoints.Num() - 1);
		return Cast<AMyPlayerStart>(ValidStartPoints[RandomIndex]);
	}

	return nullptr;
}

void AMyGameModeBase::RespawnPlayer(AMyPlayerController* Controller)
{
	if (Controller == nullptr)
		return;

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(
		this, &AMyGameModeBase::FinishRespawn, Controller);
    
	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);
}

void AMyGameModeBase::FinishRespawn(AMyPlayerController* Controller)
{
	if (Controller == nullptr)
		return;

	AMyPlayerStart* StartSpot = ChoosePlayerStart(Controller);

	if (StartSpot != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        
		APawn* NewPawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, StartSpot->GetActorLocation(), StartSpot->GetActorRotation(), SpawnParams);

		if (NewPawn != nullptr)
		{
			Controller->Possess(NewPawn);
		}
	}
}

// You'll need to implement this function to determine the initial team for a player
FGameplayTag AMyGameModeBase::DetermineInitialTeam()
{
	return FGameplayTag();
}

void AMyGameModeBase::EndGame(FGameplayTag TeamWinner)
{
	EndTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
	const float TotalTimeInSeconds = EndTime - StartTime;
	const float TotalTimeInMinutes = TotalTimeInSeconds / 60.0f;
	
	for (const auto& PlayerState : GetWorld()->GetGameState()->PlayerArray)
	{
		Cast<AMyPlayerState>(PlayerState)->NotifyEndGame(TeamWinner, TotalTimeInMinutes);
	}
}
