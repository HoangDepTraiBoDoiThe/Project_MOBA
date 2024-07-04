// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/Interface/CombatInterface.h"

UBaseAttributeSet::UBaseAttributeSet()
{
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Vital attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, HitPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxHitPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Primary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Resilient, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Resistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);

	// Secondary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, HitPointRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MagicResist, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MagicResistPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, CriticalHitMultiply, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
}

#pragma region Rep Notify Functions
void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHitPointAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHitPoint());
    }
    if (Attribute == GetManaAttribute())
    {
        NewValue = (FMath::Clamp(NewValue, 0.f, GetMaxMana()));
    }
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetHitPointAttribute())
    {
        SetHitPoint(FMath::Clamp(Data.EvaluatedData.Attribute.GetNumericValue(this), 0.f, GetMaxHitPoint()));
    }
    if (Data.EvaluatedData.Attribute == GetMaxManaAttribute())
    {
        SetMana(FMath::Clamp(Data.EvaluatedData.Attribute.GetNumericValue(this), 0.f, GetMaxMana()));
    }

    if (Data.EvaluatedData.Attribute == GetDamageIncomingAttribute())
    {
        const float IncomingDamage = Data.EvaluatedData.Attribute.GetNumericValue(this);
        SetHitPoint(GetHitPoint() - IncomingDamage);
        if (GetHitPoint() <= 0)
        {
            const int32 XP2Reward = GetThisCombatActor()->GetXPReward();

            const UAbilitySystemComponent* ASC = Data.EffectSpec.GetContext().GetInstigatorAbilitySystemComponent();
            AMyPlayerState* PlayerState = Cast<APlayerCharacter>(ASC->GetAvatarActor())->GetMyPlayerState();
            PlayerState->RewardPlayer(XP2Reward);
            GetThisCombatActor()->Die();
        }
    }
}

ICombatInterface* UBaseAttributeSet::GetThisCombatActor()
{
    if (!ThisCombatActor)
        ThisCombatActor = Cast<ICombatInterface>(GetActorInfo()->AvatarActor);
    return ThisCombatActor;
}

void UBaseAttributeSet::OnRep_HitPoint(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, HitPoint, OldValue);
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Mana, OldValue); 
}

void UBaseAttributeSet::OnRep_MaxHitPoint(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxHitPoint, OldValue); 
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxMana, OldValue); 
}

void UBaseAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Vigor, OldValue); 
}

void UBaseAttributeSet::OnRep_Resilient(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Resilient, OldValue); 
}

void UBaseAttributeSet::OnRep_Resistance(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Resistance, OldValue); 
}

void UBaseAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Strength, OldValue); 
}

void UBaseAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Intelligence, OldValue); 
}

void UBaseAttributeSet::OnRep_HitPointRegeneration(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, HitPointRegeneration, OldValue); 
}

void UBaseAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ManaRegeneration, OldValue); 
}

void UBaseAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Armor, OldValue); 
}

void UBaseAttributeSet::OnRep_MagicResist(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MagicResist, OldValue);
}

void UBaseAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ArmorPenetration, OldValue);
}

void UBaseAttributeSet::OnRep_MagicResistPenetration(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MagicResistPenetration, OldValue); 
}

void UBaseAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CriticalHitChance, OldValue); 
}

void UBaseAttributeSet::OnRep_CriticalHitMultiply(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CriticalHitMultiply, OldValue); 
}

void UBaseAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldValue) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, BlockChance, OldValue);
}
#pragma endregion
