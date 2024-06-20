// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/MyPlayerController.h"
#include "PLayerState/MyPlayerState.h"
#include "Project_MOBA/Data/HeroInfosDataAsset.h"
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
		MyAbilitySystemComponent->PlayerASCInitialize(GetMyPlayerState(), this);
		BaseAttributeSet->SetHitPoint(100);
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

TArray<TSubclassOf<UGameplayAbility>>* APlayerCharacter::GetHeroStartupAbilities() const
{
	return HeroInfos->GetStartupAbilities(GetHeroTag());
}

TMap<TObjectPtr<UInputAction>, FGameplayTag>* APlayerCharacter::GetHeroInputActionInfos() const
{
	return HeroInfos->GetInputActionInfos(GetHeroTag());
}
