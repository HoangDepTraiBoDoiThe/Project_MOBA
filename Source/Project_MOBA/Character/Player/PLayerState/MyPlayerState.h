// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class UAbilitySystemComponent;
class UBaseAttributeSet;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMyPlayerState : public APlayerState, public  IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;;
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}
protected:
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, Category=GAS)
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;
	
private:

};
