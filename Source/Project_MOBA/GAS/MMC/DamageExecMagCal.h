// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecMagCal.generated.h"

/**
 * 
 */
struct CaptureDefStruct
{
	CaptureDefStruct(const FGameplayTag& ResistTypeTag, const FGameplayEffectAttributeCaptureDefinition& BoostType, const FGameplayEffectAttributeCaptureDefinition& ResistType)
	{
		DamageResistTypeTag = ResistTypeTag;
		SourceDamageBoostType = BoostType;
		TargetDamageResistType = ResistType;
	}
	FGameplayTag DamageResistTypeTag;
	FGameplayEffectAttributeCaptureDefinition SourceDamageBoostType;
	FGameplayEffectAttributeCaptureDefinition TargetDamageResistType;
};

UCLASS()
class PROJECT_MOBA_API UDamageExecMagCal : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UDamageExecMagCal();
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResist)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistPenetration)
protected:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	TMap<FGameplayTag, CaptureDefStruct> DamageTypeTagToCaptureDefStructMap;
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagToCapTureDefMap;
	TMap<FGameplayEffectAttributeCaptureDefinition, FGameplayEffectAttributeCaptureDefinition> DamageTypeToResTypeMap;
	
};
