// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameplayEffectAbility.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FMyEffectTypeStruct
{
	GENERATED_BODY()

	FMyEffectTypeStruct() {}

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat EffectValue = 1;
};

UCLASS()
class PROJECT_MOBA_API UGameplayEffectAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	const TMap<FGameplayTag, FMyEffectTypeStruct>& GetEffectTypeMap() const {return EffectTypeMap;}

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	virtual void OrientateCharacter(FRotator Rotator);

	FActiveGameplayEffectHandle ApplyGameplayEffectWithCallerToOwner(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const UGameplayEffect* GameplayEffect, float GameplayEffectLevel, int32 Stacks = 1) const;

	UPROPERTY(EditAnywhere)
	FScalableFloat AbilityCoolDownTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, FMyEffectTypeStruct> EffectTypeMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> EffectClass;
};
