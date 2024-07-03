// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/MyPlayerController.h"
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
	PlayerInitializeGASInfos();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	PlayerInitializeGASInfos();
}

void APlayerCharacter::PlayerInitializeGASInfos()
{
	if (!GetMyPlayerState()) return;

	MyAbilitySystemComponent = Cast<UMyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetMyPlayerState()));
	BaseAttributeSet = MyPlayerState->GetBaseAttributeSet();
	if (HasAuthority())
	{
		MyAbilitySystemComponent->ActorASCInitialize(GetMyPlayerState(), this);
	}
}

AMyPlayerState* APlayerCharacter::GetMyPlayerState()
{
	if (!MyPlayerState) MyPlayerState = Cast<AMyPlayerState>(GetPlayerState());
	return MyPlayerState;
}

AMyPlayerController* APlayerCharacter::GetMyPlayerController()
{
	if (!MyPlayerController) MyPlayerController = Cast<AMyPlayerController>(GetController());
	return MyPlayerController;
}

int32 APlayerCharacter::GetXP()
{
	return GetMyPlayerState()->GetXP();
}

int32 APlayerCharacter::GetXPReward()
{
	return GetMyPlayerState()->GetXP2Give();
}

void APlayerCharacter::IncreaseXP2Give(const int32 XPAmount)
{
	return GetMyPlayerState()->IncreaseXP2Give(XPAmount);
}

int32 APlayerCharacter::GetCharacterLevel()
{
	return GetMyPlayerState()->GetPlayerLevel();
}

const TMap<TObjectPtr<UInputAction>, FGameplayTag>* APlayerCharacter::GetHeroInputActionInfos() const
{
	for (auto& Pair : InputActionInfos)
	{
		return &InputActionInfos;
	}
	return nullptr;
}
