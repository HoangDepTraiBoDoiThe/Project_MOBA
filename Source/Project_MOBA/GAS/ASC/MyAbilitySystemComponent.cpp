// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GAS/GameplayAbility/BaseGameplayAbility.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

void UMyAbilitySystemComponent::ActorASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor)
{
	InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	ApplyDefaultGEs();
	GiveStartupAbilities();
	ReceiveAndBindCallBackToDependencies();
}

bool UMyAbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag AbilityTag)
{
	for (const auto& Ability : GetActivatableAbilities())
	{
		if (Ability.Ability->AbilityTags.HasTagExact(AbilityTag))
			return TryActivateAbility(Ability.Handle);
	}
	return false;
}

void UMyAbilitySystemComponent::ApplyDefaultGEs()
{
	TSubclassOf<UGameplayEffect> PrimaryGE;
	TArray<TSubclassOf<UGameplayEffect>> SecondaryGEs;
	GetBaseCharacter()->GetCharacterInfosDataAsset()->GetDefaultGEs(BaseCharacter->GetCharacterTag(), PrimaryGE,
	                                                                SecondaryGEs);
	//CHECKF(PrimaryGE, "HIGH", UMyAbilitySystemComponent::GetName(), __FUNCTION__, "")
	if (PrimaryGE)
	{
		ApplyGameplayEffectSpecToSelf(
			*UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(this, PrimaryGE).Data.Get());
	}
	for (auto& GE : SecondaryGEs)
	{
		ApplyGameplayEffectSpecToSelf(
			*UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(this, GE).Data.Get());
	}
}

void UMyAbilitySystemComponent::GiveStartupAbilities()
{
	TArray<FCharacterAbilityStruct> AbilityData = GetBaseCharacter()->GetCharacterStartupAbilities();
	for (const auto& Struct : AbilityData)
	{
		if (Struct.ShouldGiveAbilityOnStart)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Struct.Ability, 1);
			FGameplayTag AbilityState = MyGameplayTagsManager::Get().Ability_Availability_Unlockable;
			AbilityState = MyGameplayTagsManager::Get().Ability_Availability_Unlocked;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilityState);
			GiveAbility(AbilitySpec);
			continue;
		}
		UnlockAbleAbilityTags.AddTagFast(Struct.Ability.GetDefaultObject()->GetAbilityTag());
	}
	
	const TArray<TSubclassOf<UBaseGameplayAbility>> AbilityPassiveClasses = GetBaseCharacter()->GetCharacterInfosDataAsset()->GetPassiveAbilities();
	for (const auto& AbilityClass : AbilityPassiveClasses)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		FGameplayTag AbilityState = MyGameplayTagsManager::Get().Ability_Availability_Unlocked;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityState);
		GiveAbility(AbilitySpec);
	}
}

void UMyAbilitySystemComponent::BroadCastActivatableAbilityUIData()
{
	for (const auto& AbilitySpec : GetActivatableAbilities())
	{
		const FGameplayTag AbilityTag = Cast<UBaseGameplayAbility>(AbilitySpec.Ability)->GetAbilityTag();
		const FGameplayTag AbilityState = GetAbilityUnlockStateByAbilitySpec(AbilitySpec);
		OnGameplayAbilityStatusToControllerDelegate.Broadcast(AbilityTag, AbilityState);
	}
}

FGameplayTag UMyAbilitySystemComponent::GetAbilityUnlockStateByAbilitySpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (const auto& Tag : AbilitySpec.DynamicAbilityTags)
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Ability.Availability"))) return Tag;
	return FGameplayTag();
}

void UMyAbilitySystemComponent::ClientOnAbilityStatusChange_Implementation(FGameplayTag AbilityTag, FGameplayTag AbilityState)
{
	OnGameplayAbilityStatusToControllerDelegate.Broadcast(AbilityTag, AbilityState);
}

void UMyAbilitySystemComponent::ReceiveAndBindCallBackToDependencies()
{
	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);

	for (const auto& Attribute : Attributes)
	{
		GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
			[this] (const FOnAttributeChangeData& AttributeChangeData)
			{
				OnNewAttributeValueBroadcastToControllerDelegate.Broadcast(AttributeChangeData);
			});
	}

	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this](UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec,
		       FActiveGameplayEffectHandle EffectHandle)
		{
		}
	);
	OnGameplayEffectAppliedDelegateToTarget.AddLambda(
		[this](UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle)
		{
		}
	);
}

FGameplayTagContainer UMyAbilitySystemComponent::GetLevelUpAbleAbilityTags(const int32 CharacterLevel)
{
	ABILITYLIST_SCOPE_LOCK()
	FGameplayTagContainer LevelUpAbleAbilityTags = FGameplayTagContainer();
	LevelUpAbleAbilityTags.AppendTags(UnlockAbleAbilityTags);
	FGameplayTagContainer IgnoreStates;
	IgnoreStates.AddTagFast(MyGameplayTagsManager::Get().Ability_Availability_FullyUpgraded);
	
	for (const auto& AbilitySpec : GetActivatableAbilities())
	{
		FGameplayTag AbilityTag = Cast<UBaseGameplayAbility>(AbilitySpec.Ability)->GetAbilityTag();
		if (!AbilityTag.MatchesTag(FGameplayTag::RequestGameplayTag("Ability.Primary"))) continue;

		bool bShouldAddTag = false;
		for (auto& DynamicTag : AbilitySpec.DynamicAbilityTags)
		{
			if (!DynamicTag.MatchesTag(FGameplayTag::RequestGameplayTag("Ability.Availability"))) continue;
			if (DynamicTag.MatchesAnyExact(IgnoreStates)) break;
			if (AbilityTag.MatchesTagExact(MyGameplayTagsManager::Get().Ability_Primary_R))
				bShouldAddTag = FMath::Floor(CharacterLevel / 6) > AbilitySpec.Level;
			else bShouldAddTag = true;
			break;
		}
		if (bShouldAddTag) LevelUpAbleAbilityTags.AddTagFast(AbilityTag);
	}
	return LevelUpAbleAbilityTags;
}

bool UMyAbilitySystemComponent::UnlockAbility(FGameplayTag AbilityTag)
{
	TArray<FCharacterAbilityStruct> AbilityData = GetBaseCharacter()->GetCharacterStartupAbilities();
	for (const auto& Struct : AbilityData)
	{
		if (AbilityTag.MatchesTagExact(Struct.Ability.GetDefaultObject()->GetAbilityTag()))
		{
			FGameplayTag AbilityState = MyGameplayTagsManager::Get().Ability_Availability_Unlocked;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Struct.Ability, 1);
			AbilitySpec.DynamicAbilityTags.AddTag(AbilityState);
			GiveAbility(AbilitySpec);
			UnlockAbleAbilityTags.RemoveTag(AbilityTag);
			return true;
		}
	}
	return false;
}

bool UMyAbilitySystemComponent::AbilityLeveling(const FGameplayTag AbilityTag, const int32 CharacterLevel)
{
	ABILITYLIST_SCOPE_LOCK()
	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.Ability->AbilityTags.HasTag(AbilityTag)) continue;
		bool bShouldUpgrade;
		
		if (AbilitySpec.Ability->AbilityTags.HasTagExact(MyGameplayTagsManager::Get().Ability_Primary_R))
			bShouldUpgrade = FMath::Floor(CharacterLevel / 6) > AbilitySpec.Level;
		else bShouldUpgrade = AbilitySpec.Ability->AbilityTags.HasTagExact(AbilityTag) && AbilitySpec.Level < 4;
		
		if (bShouldUpgrade)
		{
			AbilitySpec.Level += 1;
			MarkAbilitySpecDirty(AbilitySpec);
		}
		return true;
	}
	return false;
}

void UMyAbilitySystemComponent::Server_LevelUpAbility_Implementation(const FGameplayTag AbilityTag, const int32 CharacterLevel)
{
	if (AbilityTag.MatchesAnyExact(UnlockAbleAbilityTags))
		if (UnlockAbility(AbilityTag)) return;
	AbilityLeveling(AbilityTag, CharacterLevel);
}

ABaseCharacter* UMyAbilitySystemComponent::GetBaseCharacter()
{
	if (!BaseCharacter) BaseCharacter = Cast<ABaseCharacter>(GetAvatarActor());
	return BaseCharacter;
}
