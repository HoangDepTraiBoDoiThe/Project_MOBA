// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;

/**
 * 
 */

UCLASS()
class PROJECT_MOBA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraArmComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> CameraRootComponent;
	virtual void BeginPlay() override;

	
private:
	
};
