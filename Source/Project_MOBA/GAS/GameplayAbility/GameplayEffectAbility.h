// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameplayEffectAbility.generated.h"

/**
 * 
 */
USTRUCT()
struct FMyEffectTypeStruct
{
	GENERATED_BODY()

	FMyEffectTypeStruct() {}
	explicit FMyEffectTypeStruct(const float EffectValue) : EffectValue(EffectValue) {}

	UPROPERTY(EditDefaultsOnly)
	float EffectValue = 1;
};

UCLASS()
class PROJECT_MOBA_API UGameplayEffectAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	const TMap<FGameplayTag, FMyEffectTypeStruct>& GetEffectTypeMap() const {return EffectTypeMap;}

protected:
	virtual void OrientateCharacter(FRotator Rotator);

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, FMyEffectTypeStruct> EffectTypeMap;
	
};
