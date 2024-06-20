// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"

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

USkeletalMeshComponent* ABaseCharacter::GetAttackableActorMesh()
{
	return GetMesh();
}

UMyAbilitySystemComponent* ABaseCharacter::GetMyASC()
{
	return MyAbilitySystemComponent;
}

void ABaseCharacter::ApplyEffectSpecToSelf(const FGameplayEffectSpec& SpecToApply)
{
	MyAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(SpecToApply);
}
