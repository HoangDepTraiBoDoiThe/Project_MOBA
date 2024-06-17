// Cu Nhat Hoang


#include "MyGameplayTagsManager.h"

#include "GameplayTagsManager.h"

MyGameplayTagsManager MyGameplayTagsManager::GameplayTags;

MyGameplayTagsManager::MyGameplayTagsManager()
{
}

MyGameplayTagsManager& MyGameplayTagsManager::Get()
{
	return GameplayTags;
}

void MyGameplayTagsManager::InitNativeGameplayTags()
{
/*
 *	Hero tags
 */
	MyGameplayTagsManager::GameplayTags.Hero_Murdock = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Hero.Murdock"),
		FString(
			"")
	);
	
/*
 *	Vital attributes
 */
	MyGameplayTagsManager::GameplayTags.Attribute_Vital_HitPoint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Vital.HitPoint"),
		FString(
			"Numeric representation of a character's life force, indicating the amount of damage they can endure before succumbing to defeat."));

	MyGameplayTagsManager::GameplayTags.Attribute_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Vital.Mana"),
		FString(
			"Magical energy or power, associated with casting spells or performing supernatural actions like casting spells"));
	/*
	*	Primary attributes
	*/
	MyGameplayTagsManager::GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Primary.Intelligence"), FString("Directly affect maximum mana and mana regeneration."));

	MyGameplayTagsManager::GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Strength"), FString("Influence physical power."));

	MyGameplayTagsManager::GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Resilience"),
		FString("Impacts the character's resistances, including 'Armor' and 'Armor penetration.'"));

	MyGameplayTagsManager::GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Vigor"),
		FString("Impacts the character's 'Maximum HitPoint' and 'Heal Regeneration.'"));

	/*
	*	Secondary attributes
	*/
	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.Armor"),
		FString("Impacted by 'Resilience'. Reduces damage taken. Improve 'Block Chance' and 'Critical Hit Res'."));

	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Secondary.ArmorPenetration"),
			FString("Impacted by 'Resilience'. Ignore percentage of enemy 'Armor'. Increases 'Critical Hit Chance'."));

	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Secondary.BlockChance"), FString("Impacted by 'Armor'. Chance to cut damage in half"));

	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Secondary.CriticalHitChance"),
			FString("Impacted by 'ArmorPenetration'. Chance to double plus Critical Hit bonus."));

	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_CriticalHitMultiply = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Secondary.CriticalHitMultiply"),
			FString(""));

	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_HitPointRegeneration = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Secondary.HealthRegeneration"),
			FString("Impacted by 'Vigor'. Amount of 'HitPoint' regenerated every 1 second"));

	MyGameplayTagsManager::GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Secondary.ManaRegeneration"),
			FString("Impacted by 'Intelligence'. Amount of 'Mana' regenerated every 1 second"));

	MyGameplayTagsManager::GameplayTags.Attribute_Vital_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.MaxMana"),
		FString("Impacted by 'Intelligence'. Maximum amount of 'Mana' obtainable"));

	MyGameplayTagsManager::GameplayTags.Attribute_Vital_MaxHitPoint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.MaxHitPoint"),
		FString("Impacted by 'Vigor'. Maximum amount of 'Hit Point' obtainable"));

	/*
	*	Damage type Tags
	*/
	MyGameplayTagsManager::GameplayTags.DamageType_Elemental_Physical = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("DamageType.Elemental.Physical"),
			FString(""));
	MyGameplayTagsManager::GameplayTags.DamageType_Elemental_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageType.Elemental.Fire"),
		FString(""));
	MyGameplayTagsManager::GameplayTags.DamageType_Elemental_Water = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageType.Elemental.Water"),
		FString(""));
	MyGameplayTagsManager::GameplayTags.DamageType_Elemental_Wind = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("DamageType.Elemental.Wind"),
		FString(""));

	GameplayTags.DamageTypeNames.Add(MyGameplayTagsManager::Get().DamageType_Elemental_Physical, FName("Physical"));
	GameplayTags.DamageTypeNames.Add(MyGameplayTagsManager::Get().DamageType_Elemental_Fire, FName("Fire"));
	GameplayTags.DamageTypeNames.Add(MyGameplayTagsManager::Get().DamageType_Elemental_Water, FName("Water"));
	GameplayTags.DamageTypeNames.Add(MyGameplayTagsManager::Get().DamageType_Elemental_Wind, FName("Wind"));

	MyGameplayTagsManager::GameplayTags.Attribute_Resistance_Elemental_Fire = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Resistance.Elemental.Fire"),
			FString(""));
	MyGameplayTagsManager::GameplayTags.Attribute_Resistance_Elemental_Water = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Resistance.Elemental.Water"),
			FString(""));
	MyGameplayTagsManager::GameplayTags.Attribute_Resistance_Elemental_Wind = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Resistance.Elemental.Wind"),
			FString(""));
	MyGameplayTagsManager::GameplayTags.Attribute_Resistance_Physical = UGameplayTagsManager::Get().
		AddNativeGameplayTag(
			FName("Attribute.Resistance.Physical"),
			FString(""));

	/*
	 *	Meta attribute Tags
	 */
	MyGameplayTagsManager::GameplayTags.Attribute_Meta_HitPoint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Meta.HitPoint"),
		FString(""));
	MyGameplayTagsManager::GameplayTags.Attribute_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Meta.IncomingXP"),
		FString(""));

	/*
	 * Ability Input Tags 
	 */
	MyGameplayTagsManager::GameplayTags.Test_Ability_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Testing"),
		FString("Test_Ability_1"));
	MyGameplayTagsManager::GameplayTags.Control_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Control_LMB"),
		FString("Left mouse button"));
	MyGameplayTagsManager::GameplayTags.Control_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Control_RMB"),
		FString("Right mouse button"));
	/*
	 * Ability Cooldown and Cost 
	 */
	GameplayTags.Ability_Cooldown_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Cooldown.FireBolt"),
		FString(""));

	MyGameplayTagsManager::GameplayTags.Effects_OnHitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.OnHitReact"),
		FString("OnHitReact"));

	/*
	 *	Ability Availability Status Tags
	 */
	GameplayTags.Ability_Availability_NotUnlockable = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Availability.NotUnlockable"),
		FString(""));
	GameplayTags.Ability_Availability_Unlockable = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Availability.Unlockable"),
		FString(""));
	GameplayTags.Ability_Availability_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Availability.Unlocked"),
		FString(""));
	GameplayTags.Ability_Availability_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Availability.Equipped"),
		FString(""));

	/*
	 *	Ability Availability Status Tags
	 */
	GameplayTags.Ability_Projectile_FireBall = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Projectile.FireBall"),
		FString(""));
	GameplayTags.Ability_Projectile_LightingBall = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Ability.Projectile.LightingBall"),
		FString(""));
}