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
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

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

		AActor* NewPawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, DefaultPawnClass, StartSpot->GetTransform(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

		if (NewPawn)
		{

			// Set the team tag for the new pawn here if necessary
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(NewPawn);
			if (PlayerCharacter)
			{
				// You might want to implement logic here to determine the initial team
				// For example, based on the number of players on each team
				PlayerCharacter->SetTeamTag(DetermineInitialTeam());
			}
			UGameplayStatics::FinishSpawningActor(NewPawn, StartSpot->GetTransform());
		}

		return Cast<APawn>(NewPawn);
	}

	return nullptr;
}

TArray<AActor*> AMyGameModeBase::FindAllPlayerStarts(UWorld* World)
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World, AMyPlayerStart::StaticClass(), PlayerStarts);
	return PlayerStarts;
}

AMyPlayerStart* AMyGameModeBase::ChoosePlayerStart(const AController* Controller)
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
		PlayerTeamTag = DetermineInitialTeam();
	}

	// Filter start points based on team tag
	for (AActor* StartPoint : AllPlayerStarts)
	{
		AMyPlayerStart* MyPlayerStart = Cast<AMyPlayerStart>(StartPoint);
		if (MyPlayerStart->GetTeamTag().MatchesTagExact(PlayerTeamTag))
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

	Cast<AMyPlayerController>(Controller)->GetPlayerCharacter()->Reset();
	Cast<AMyPlayerController>(Controller)->GetPlayerCharacter()->Destroy();
	if (StartSpot != nullptr)
	{
		RestartPlayerAtPlayerStart(Controller, StartSpot);
	}
}

FGameplayTag AMyGameModeBase::DetermineInitialTeam() const
{
	for (APlayerState* PlayerState : GetWorld()->GetGameState()->PlayerArray)
	{
		AMyPlayerState* MyPlayerState = Cast<AMyPlayerState>(PlayerState);
		if (!MyPlayerState->GetPlayerCharacter()) return MyGameplayTagsManager::Get().Team_White;
		const FGameplayTag ChoosingTeam = MyPlayerState->GetPlayerCharacter()->GetTeamTag().MatchesTagExact(MyGameplayTagsManager::Get().Team_White) ? MyGameplayTagsManager::Get().Team_Black : MyGameplayTagsManager::Get().Team_White;
		return ChoosingTeam;
	}
	return MyGameplayTagsManager::Get().Team_White;
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
