// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AMyPlayerStart;
class AMyPlayerController;
class AMotherBase;
class ATurret;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void StartPlay() override;
	TMap<FGameplayTag, AMotherBase*> GetTeamBaseMap() {return TeamBaseMap;}

	FGameplayTag DetermineInitialTeam();
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;
	TArray<AActor*> FindAllPlayerStarts(UWorld* World);
	AMyPlayerStart* ChoosePlayerStart(AController* Controller);

	void EndGame(FGameplayTag TeamWinner);
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void RespawnPlayer(AMyPlayerController* Controller);
	void FinishRespawn(AMyPlayerController* Controller);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyPlayerStart> MyPlayerStartClass;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	float RespawnDelay = 5.0f;
	float StartTime;
	float EndTime;
	UPROPERTY()
	TMap<FGameplayTag, AMotherBase*> TeamBaseMap;

	
};
