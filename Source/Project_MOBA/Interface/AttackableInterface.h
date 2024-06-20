// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackableInterface.generated.h"

struct FGameplayEffectSpec;
class UMyAbilitySystemComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_MOBA_API IAttackableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual USkeletalMeshComponent* GetAttackableActorMesh() = 0;
	virtual UMyAbilitySystemComponent* GetMyASC() = 0;
	virtual void ApplyEffectSpecToSelf(const FGameplayEffectSpec& SpecToApply) = 0;
};