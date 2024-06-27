// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameplayEffectAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UGameplayEffectAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	const TMap<FGameplayTag, float>& GetDamageTypes() const {return DamageTypes;}

protected:
	virtual void OrientateCharacter(FRotator Rotator);
	
	TMap<FGameplayTag, float> DamageTypes;
	
};
