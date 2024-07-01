// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GAS/GameplayAbility/BaseGameplayAbility.h"

void UMyAbilitySystemComponent::ActorASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor)
{
	InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	ApplyDefaultGEs();
	GiveStartupAbilities();
	ReceiveAndBindCallBackToDependencies();
}

bool UMyAbilitySystemComponent::TryActivateAbilityByInputTag(const FGameplayTag InputTag)
{
	for (const auto& Ability : GetActivatableAbilities())
	{
		if (Ability.Ability->AbilityTags.HasTagExact(InputTag))
			return TryActivateAbility(Ability.Handle);
	}		
	return false;
}

void UMyAbilitySystemComponent::ApplyDefaultGEs()
{
	TSubclassOf<UGameplayEffect> PrimaryGE;
	TArray<TSubclassOf<UGameplayEffect>> SecondaryGEs;
	GetBaseCharacter()->GetCharacterInfosDataAsset()->GetDefaultGEs(BaseCharacter->GetCharacterTag(), PrimaryGE, SecondaryGEs);
	//CHECKF(PrimaryGE, "HIGH", UMyAbilitySystemComponent::GetName(), __FUNCTION__, "")
	if (PrimaryGE)
	{
		ApplyGameplayEffectSpecToSelf(*UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(this, PrimaryGE).Data.Get());
	}
	for (auto& GE : SecondaryGEs)
	{
		ApplyGameplayEffectSpecToSelf(*UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(this, GE).Data.Get());
	}
}

void UMyAbilitySystemComponent::GiveStartupAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>>* AbilityClasses = GetBaseCharacter()->GetCharacterStartupAbilities();
	if (!AbilityClasses || AbilityClasses->Num() == 0) return;
	for (const auto& AbilityClass : *AbilityClasses)
	{
		FGameplayAbilitySpec Ability = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbility(Ability);
	}
}

void UMyAbilitySystemComponent::ReceiveAndBindCallBackToDependencies()
{
	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);
	for (const FGameplayAttribute& Attribute : Attributes)
	{
		GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
			[this] (const FOnAttributeChangeData& AttributeChangeData)
			{
				
			}
		);
	}
	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this] (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
		{
			
		}
	);
	OnGameplayEffectAppliedDelegateToTarget.AddLambda(
		[this] (UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle)
		{
			
		}
	);
}

ABaseCharacter* UMyAbilitySystemComponent::GetBaseCharacter()
{
	if (!BaseCharacter) BaseCharacter = Cast<ABaseCharacter>(GetAvatarActor());
	return BaseCharacter;
}
