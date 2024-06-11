// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "MyEnhancedInputComponent.generated.h"

/**
 * 
 */

UCLASS()
class PROJECT_MOBA_API UMyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename InputPressFuncType, typename InputHeldFuncType, typename InputReleaseFuncType>
	void SetupInputActions(TMap<TObjectPtr<UInputAction>, FGameplayTag> HeroInfos, UserClass* Object , InputPressFuncType InputPressFunc, InputHeldFuncType InputHeldFunc, InputReleaseFuncType InputReleaseFunc);

protected:
	
};

template <class UserClass, typename InputPressFuncType, typename InputHeldFuncType, typename InputReleaseFuncType>
void UMyEnhancedInputComponent::SetupInputActions(TMap<TObjectPtr<UInputAction>, FGameplayTag> HeroInfos,
	UserClass* Object, InputPressFuncType InputPressFunc, InputHeldFuncType InputHeldFunc,
	InputReleaseFuncType InputReleaseFunc)
{
	for (TTuple<TObjectPtr<UInputAction>, FGameplayTag>& Pair : HeroInfos)
	{
		if (InputPressFunc) BindAction(Pair.Key, ETriggerEvent::Started, Object, InputPressFunc, Pair.Value);
		if (InputPressFunc) BindAction(Pair.Key, ETriggerEvent::Started, Object, InputHeldFunc, Pair.Value);
		if (InputPressFunc) BindAction(Pair.Key, ETriggerEvent::Completed, Object, InputReleaseFunc, Pair.Value);
	}
}
