// Cu Nhat Hoang


#include "DamageExecMagCal.h"

#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

UDamageExecMagCal::UDamageExecMagCal()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Strength, Source, false)
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MagicResist, Target, false)
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, MagicResistPenetration, Source, false)
	RelevantAttributesToCapture.Add(StrengthDef);
	RelevantAttributesToCapture.Add(MagicResistDef);
	RelevantAttributesToCapture.Add(MagicResistPenetrationDef);

	const CaptureDefStruct CaptureDefInfos = CaptureDefStruct(MyGameplayTagsManager::Get().Attribute_Secondary_MagicResist, MagicResistPenetrationDef, MagicResistDef);
	DamageTypeTagToCaptureDefStructMap.Add(MyGameplayTagsManager::Get().DamageType_Elemental_Magic, CaptureDefInfos);
}

void UDamageExecMagCal::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float Damage = 0;
	for (const FGameplayTag& DamageTypeTag : MyGameplayTagsManager::Get().DamageTypes)
	{
		const CaptureDefStruct* CaptureInfo = DamageTypeTagToCaptureDefStructMap.Find(DamageTypeTag);
		const float DamageType = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(DamageTypeTag, false);
		float SourceDamageBoostMag;
		float TargetDamageResistMag;
		if (CaptureInfo)
		{
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureInfo->SourceDamageBoostType, FAggregatorEvaluateParameters(), SourceDamageBoostMag);
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureInfo->TargetDamageResistType, FAggregatorEvaluateParameters(), TargetDamageResistMag);
		}
		const float DamageTypeAfterCal = DamageType + SourceDamageBoostMag - TargetDamageResistMag;
		Damage += DamageTypeAfterCal;
	}

	FGameplayModifierEvaluatedData EvaluatedData;
	EvaluatedData.ModifierOp = EGameplayModOp::Additive;
	EvaluatedData.Magnitude = Damage;
	EvaluatedData.Attribute = UBaseAttributeSet::GetDamageIncomingAttribute();
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
