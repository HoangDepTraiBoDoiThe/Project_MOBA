// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "DamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UDamageAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	const TMap<FGameplayTag, float>& GetDamageTypes() const {return DamageTypes;}

protected:
	TMap<FGameplayTag, float> DamageTypes;
	
};
