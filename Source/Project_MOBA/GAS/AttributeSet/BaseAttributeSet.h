// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECT_MOBA_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// Vital attributes
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HitPoint)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHitPoint)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana)

	// Primary attributes
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Vigor)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Resilient)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Resistance)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Strength)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Intelligence)

	// Secondary attributes
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HitPointRegeneration)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ManaRegeneration)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Armor)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MagicResist)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ArmorPenetration)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MagicResistPenetration)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalHitChange)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, BlockChange)

protected:

private:
#pragma region Rep Notify Functions
	// Vital attributes
	UFUNCTION()
	void OnRep_HitPoint(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxHitPoint(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;

	// Primary attributes
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Resilient(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Resistance(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue) const;

	// Secondary attributes
	UFUNCTION()
	void OnRep_HitPointRegeneration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MagicResist(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MagicResistPenetration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_CriticalHitChange(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_BlockChange(const FGameplayAttributeData& OldValue) const;
#pragma endregion

#pragma region Vital attributes
    // Current health of the character
    UPROPERTY(ReplicatedUsing=OnRep_HitPoint)
    FGameplayAttributeData HitPoint;

    // Current mana/energy/resource of the character
    UPROPERTY(ReplicatedUsing=OnRep_Mana)
    FGameplayAttributeData Mana;

    // Maximum possible health of the character
    UPROPERTY(ReplicatedUsing=OnRep_MaxHitPoint)
    FGameplayAttributeData MaxHitPoint;

    // Maximum possible mana/energy/resource of the character
    UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
    FGameplayAttributeData MaxMana;
#pragma endregion

#pragma region Primary attributes
    // Influences health and physical damage
    UPROPERTY(ReplicatedUsing=OnRep_Vigor)
    FGameplayAttributeData Vigor;

    // Influences defensive capabilities and resistance to status effects
    UPROPERTY(ReplicatedUsing=OnRep_Resilient)
    FGameplayAttributeData Resilient;

    // Influences resistance to elemental/magic damage
    UPROPERTY(ReplicatedUsing=OnRep_Resistance)
    FGameplayAttributeData Resistance;

    // Influences physical attack power and related abilities
    UPROPERTY(ReplicatedUsing=OnRep_Strength)
    FGameplayAttributeData Strength;

    // Influences magical attack power and related abilities
    UPROPERTY(ReplicatedUsing=OnRep_Intelligence)
    FGameplayAttributeData Intelligence;
#pragma endregion

#pragma region Secondary attributes
    // Rate at which health regenerates
    UPROPERTY(ReplicatedUsing=OnRep_HitPointRegeneration)
    FGameplayAttributeData HitPointRegeneration;

    // Rate at which mana/energy/resource regenerates
    UPROPERTY(ReplicatedUsing=OnRep_ManaRegeneration)
    FGameplayAttributeData ManaRegeneration;

    // Physical damage reduction
    UPROPERTY(ReplicatedUsing=OnRep_Armor)
    FGameplayAttributeData Armor;

    // Magical damage reduction
    UPROPERTY(ReplicatedUsing=OnRep_MagicResist)
    FGameplayAttributeData MagicResist;

    // Amount of armor ignored when dealing physical damage
    UPROPERTY(ReplicatedUsing=OnRep_ArmorPenetration)
    FGameplayAttributeData ArmorPenetration;

    // Amount of magic resist ignored when dealing magical damage
    UPROPERTY(ReplicatedUsing=OnRep_MagicResistPenetration)
    FGameplayAttributeData MagicResistPenetration;

    // Chance to deal increased damage
    UPROPERTY(ReplicatedUsing=OnRep_CriticalHitChange)
    FGameplayAttributeData CriticalHitChange;

    // Chance to reduce incoming damage
    UPROPERTY(ReplicatedUsing=OnRep_BlockChange)
    FGameplayAttributeData BlockChange;
#pragma endregion
	
#pragma region Meta attributes
	FGameplayAttributeData XPIncoming;
	FGameplayAttributeData DamageIncoming;
#pragma endregion
};
