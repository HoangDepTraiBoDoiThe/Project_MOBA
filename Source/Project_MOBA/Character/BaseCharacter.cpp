// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Minion/Controller/MyAIController.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

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

USkeletalMeshComponent* ABaseCharacter::GetAttackableActorMesh()
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
	bool bSuccessfull = MyAbilitySystemComponent->TryActivateAbilityByTag(MyGameplayTagsManager::Get().Ability_Passive_Die);
	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Try activate ability %s is %s"), *MyGameplayTagsManager::Get().Ability_Passive_Die.GetTagName().ToString(), bSuccessfull ? *FString("Successfully") : *FString("Failed")));
}

void ABaseCharacter::Death()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}


const UAnimMontage* ABaseCharacter::GetAnimMontageByTag(const FGameplayTag Tag) const
{
	return nullptr;
}

TArray<UParticleSystem*> ABaseCharacter::GetParticleSystems() const
{
	TArray<TObjectPtr<UParticleSystem>> OutParticleSystems;
	CharacterInfos->GetParticleSystems(GetCharacterTag(), OutParticleSystems);
	return OutParticleSystems;
}

TArray<TSubclassOf<UGameplayAbility>> ABaseCharacter::GetCharacterStartupAbilities() const
{
	TArray<TSubclassOf<UGameplayAbility>> OutStartupAbilities;
	CharacterInfos.Get()->GetStartupAbilities(GetCharacterTag(), OutStartupAbilities);
	return OutStartupAbilities;
}
