// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter()
{
	CameraRootComponent = CreateDefaultSubobject<USceneComponent>(FName("Camera root component"));
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName("Camera arm component"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera component"));

	CameraArmComponent->SetupAttachment(CameraRootComponent);
	CameraComponent->SetupAttachment(CameraArmComponent);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraRootComponent->SetWorldLocation(GetActorLocation());
}
