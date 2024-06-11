// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UAbilitySystemComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;

UCLASS()
class PROJECT_MOBA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;

};
