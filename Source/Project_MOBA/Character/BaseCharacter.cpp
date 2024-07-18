// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Project_MOBA.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_MOBA/Component/EnvironmentComponent.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);

	MeleCollisionBoundary = CreateDefaultSubobject<UBoxComponent>(FName("MeleCollisionBoundary"));
	MeleCollisionBoundary->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleCollisionBoundary->SetupAttachment(GetMesh(), MeleSocketName);

	EnvironmentComponent = CreateDefaultSubobject<UEnvironmentComponent>(FName("Environment Component"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnvironmentComponent->SetWidgetControllerToWidget();
	if (GetController() && GetController()->IsPlayerController()) WidgetComponent->DestroyComponent();
}

void ABaseCharacter::Destroyed()
{
	TArray<TObjectPtr<UParticleSystem>> OutParticleSystems;
	CharacterInfos->GetParticleSystems(GetActorTag(), OutParticleSystems);
	for (const auto& Item : OutParticleSystems)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Item, GetActorTransform());
	}
	Super::Destroyed();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return MyAbilitySystemComponent;
}

UMyAbilitySystemComponent* ABaseCharacter::GetMyAbilitySystemComponent() const
{
	return MyAbilitySystemComponent;
}

UPrimitiveComponent* ABaseCharacter::GetAttackableActor_Mesh()
{
	return GetMesh();
}

FVector ABaseCharacter::GetWeaponSocketLocationByName(const FName SocketName)
{
	return GetMesh()->GetSocketLocation(SocketName);
}

void ABaseCharacter::Die()
{
	GetCharacterMovement()->StopMovementImmediately();
	FMovementProperties MovementProperties;
	MovementProperties.bCanCrouch = false;
	MovementProperties.bCanFly = false;
	MovementProperties.bCanJump = false;
	MovementProperties.bCanWalk = false;
	MovementProperties.bCanSwim = false;
	GetCharacterMovement()->MovementState = MovementProperties;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	
	GetMesh()->SetCollisionObjectType(ECC_WorldStatic);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Ground, ECR_Block);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldStatic);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Ground, ECR_Block);
	
	bool bSuccessfull = MyAbilitySystemComponent->TryActivateAbilityByTag(MyGameplayTagsManager::Get().Ability_Passive_Die);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Try activate ability %s is %s"), *MyGameplayTagsManager::Get().Ability_Passive_Die.GetTagName().ToString(), bSuccessfull ? *FString("Successfully") : *FString("Failed")));
}

void ABaseCharacter::Death()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetMesh()->SetEnableGravity(true);
}

FGameplayTag ABaseCharacter::GetTeamTag()
{
	return TeamTag;
}

FGameplayTag ABaseCharacter::GetActorTag()
{
	return CharacterTag;
}

UAnimMontage* ABaseCharacter::GetAnimMontageByTag(const FGameplayTag Tag)
{
	return CharacterInfos->GetMontageByTag(GetActorTag(), Tag);
}

TArray<FCharacterAbilityStruct> ABaseCharacter::GetCharacterStartupAbilities()
{
	TArray<FCharacterAbilityStruct> OutStartupAbilities;
	CharacterInfos.Get()->GetStartupAbilities(GetActorTag(), OutStartupAbilities);
	return OutStartupAbilities;
}

void ABaseCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AddTag(CharacterTag);
	TagContainer.AddTag(TeamTag);
}

void ABaseCharacter::IncreaseXP2Give(const int32 XPAmount)
{
	XP2Give += XPAmount;
}

int32 ABaseCharacter::GetXP()
{
	return XP;
}

int32 ABaseCharacter::GetXPReward()
{
	return XP2Give;
}

UWidgetComponent* ABaseCharacter::GetWidgetComponent() const
{
	return WidgetComponent;
}

void ABaseCharacter::SetCurrentTargetActor(ABaseCharacter* Actor)
{
	CurrentTargetActor = Actor;
}

