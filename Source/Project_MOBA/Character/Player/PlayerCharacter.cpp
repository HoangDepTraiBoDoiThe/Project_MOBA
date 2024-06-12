// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PLayerState/MyPlayerState.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

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

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SetPlayerCharacterGASInfos();
}

void APlayerCharacter::SetPlayerCharacterGASInfos()
{
	if (!GetMyPlayerState()) return;

	AbilitySystemComponent = Cast<UMyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetMyPlayerState()));
	BaseAttributeSet = MyPlayerState->GetBaseAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(GetMyPlayerState(), this);
	BaseAttributeSet->SetHitPoint(100);
}

AMyPlayerState* APlayerCharacter::GetMyPlayerState()
{
	if (!MyPlayerState) MyPlayerState = Cast<AMyPlayerState>(GetPlayerState());
	return MyPlayerState;
}
