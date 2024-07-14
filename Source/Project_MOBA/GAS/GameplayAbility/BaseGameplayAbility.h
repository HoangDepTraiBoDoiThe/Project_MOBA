// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBaseGameplayAbility();
	FGameplayTag GetAbilityTag() const {return AbilityTag;}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AbilityAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AbilityTag;
};
