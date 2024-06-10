// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "MyEnhancedInputComponent.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_MOBA_API UMyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UMyEnhancedInputComponent();

	void SetupInputActions();

protected:
	
};
