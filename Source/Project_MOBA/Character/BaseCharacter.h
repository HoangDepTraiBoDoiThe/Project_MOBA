// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Project_MOBA/Interface/AttackableInterface.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "BaseCharacter.generated.h"

class UAbilitySystemComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;

UCLASS()
class PROJECT_MOBA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IAttackableInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}

	virtual USkeletalMeshComponent* GetAttackableActorMesh() override;
	virtual UMyAbilitySystemComponent* GetMyASC() override;
	virtual void ApplyEffectSpecToSelf(const FGameplayEffectSpec& SpecToApply) override;
	virtual FVector GetWeaponSocketLocationByName(FName SocketName) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;

};
