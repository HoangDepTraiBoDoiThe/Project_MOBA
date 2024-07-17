// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

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
	TMap<FGameplayTag, AMotherBase*>& GetTeamBaseMap() {return TeamBaseMap;}
	void EndGame();
	
private:
	UPROPERTY()
	TMap<FGameplayTag, AMotherBase*> TeamBaseMap;

	
};
