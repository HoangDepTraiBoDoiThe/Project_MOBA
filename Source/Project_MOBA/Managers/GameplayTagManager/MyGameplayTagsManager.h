// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
class PROJECT_MOBA_API MyGameplayTagsManager
{
public:
	MyGameplayTagsManager();
	static MyGameplayTagsManager& Get();
 static void InitNativeGameplayTags();

 /*
  *	Character tags
  */
 FGameplayTag Character_Hero_Murdock;
 FGameplayTag Character_Hero_Gideon;
 FGameplayTag Character_Hero_GrimEXE;
 FGameplayTag Character_Minion_Normal_Mele;
 FGameplayTag Character_Minion_Normal_Range;
 FGameplayTag Character_Minion_Super_Mele;
 FGameplayTag Character_Minion_Super_Range;

/*
 *	Vital attributes
 */
 FGameplayTag Attribute_Vital_HitPoint;
 FGameplayTag Attribute_Vital_Mana;
 FGameplayTag Attribute_Vital_MaxMana;
 FGameplayTag Attribute_Vital_MaxHitPoint;

 /*
  *	Primary attributes
  */
 FGameplayTag Attribute_Primary_Intelligence;
 FGameplayTag Attribute_Primary_Strength;
 FGameplayTag Attribute_Primary_Vigor;
 FGameplayTag Attribute_Primary_Resilience;
 FGameplayTag Attribute_Primary_Resistance;
	
 /*
  *	Secondary attributes
  */
 FGameplayTag Attribute_Secondary_HitPointRegeneration;
 FGameplayTag Attribute_Secondary_ManaRegeneration;
 FGameplayTag Attribute_Secondary_Armor;
 FGameplayTag Attribute_Secondary_MagicResist;
 FGameplayTag Attribute_Secondary_ArmorPenetration;
 FGameplayTag Attribute_Secondary_MagicResistPenetration;
 FGameplayTag Attribute_Secondary_CriticalHitChance;
 FGameplayTag Attribute_Secondary_CriticalHitMultiply;
 FGameplayTag Attribute_Secondary_BlockChance;
 
 /*
  *	Damage type Tags
  */
 FGameplayTag DamageType_Physical_Base;
 FGameplayTag DamageType_Elemental_Fire;
 FGameplayTag DamageType_Elemental_Water;
 FGameplayTag DamageType_Elemental_Wind;
 FGameplayTag DamageType_Elemental_Magic;
 TArray<FGameplayTag> DamageTypes;
 TMap<FGameplayTag, FName> DamageTypeNames;

 FGameplayTag Attribute_Resistance_Physical;
 FGameplayTag Attribute_Resistance_Elemental_Fire;
 FGameplayTag Attribute_Resistance_Elemental_Water;
 FGameplayTag Attribute_Resistance_Elemental_Wind;
 
 /*
  *	Meta attribute Tags
  */
 FGameplayTag Attribute_Meta_HitPoint;
 FGameplayTag Attribute_Meta_IncomingXP;
 
 /*
  * Ability Input Tags 
  */
 FGameplayTag Control_LMB;
 FGameplayTag Control_RMB;
 FGameplayTag Control_Q;
 FGameplayTag Control_W;
 FGameplayTag Control_E;
 FGameplayTag Control_R;
 FGameplayTag Control_D;
 FGameplayTag Control_F;
 FGameplayTag Control_1;
 FGameplayTag Control_2;
 FGameplayTag Control_3;
 FGameplayTag Control_4;
 FGameplayTag Control_5;
 FGameplayTag Control_6;
 FGameplayTag Control_Movement;
 FGameplayTag Test_Ability_1;

 /*
  * Ability Cooldown and Cost 
  */
  FGameplayTag Ability_Cooldown_FireBolt;

 /*
  *	Ability Availability Status Tags
  */
 FGameplayTag Ability_Availability_NotUnlockable;
 FGameplayTag Ability_Availability_Unlockable;
 FGameplayTag Ability_Availability_Unlocked;
 FGameplayTag Ability_Availability_Equipped;
 
 /*
  *	Ability Tags
  */
 FGameplayTag Ability_Primary_Q;
 FGameplayTag Ability_Primary_W;
 FGameplayTag Ability_Primary_E;
 FGameplayTag Ability_Primary_R;
 
 FGameplayTag Ability_Passive_Die;
 FGameplayTag Ability_Passive_CanNotDie;
 FGameplayTag Ability_Projectile_FireBall;
 FGameplayTag Ability_Projectile_LightingBall;

 /*
 * Other 
 */
 FGameplayTag Effects_OnHitReact;
	
private:
	static MyGameplayTagsManager GameplayTags;
	
};
