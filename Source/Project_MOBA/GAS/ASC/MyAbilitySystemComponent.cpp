// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/GAS/GameplayAbility/BaseGameplayAbility.h"

bool UMyAbilitySystemComponent::TryActivateAbilityByInputTag(const FGameplayTag InputTag)
{
	
	for (auto& Ability : GetActivatableAbilities())
	{
		if (Ability.Ability->AbilityTags.HasTagExact(InputTag))
			return TryActivateAbility(Ability.Handle);
	}		
	return false;
}

void UMyAbilitySystemComponent::PlayerASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor)
{
	InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	for (auto& AbilityClass : *Cast<APlayerCharacter>(GetAvatarActor())->GetHeroStartupAbilities())
	{
		FGameplayAbilitySpec Ability = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbility(Ability);
	}

	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);
	for (FGameplayAttribute& Attribute : Attributes)
	{
		GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
			[this] (const FOnAttributeChangeData& AttributeChangeData)
			{
				const FOnAttributeChangeData* TestAttributeChangeData = &AttributeChangeData;
			}
		);
	}

	OnGameplayEffectAppliedDelegateToSelf.AddLambda(
		[this] (UAbilitySystemComponent* ASC, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle EffectHandle)
		{
			const FGameplayEffectSpec* TestEffectSpec = &EffectSpec;
		}
	);
	OnGameplayEffectAppliedDelegateToTarget.AddLambda(
		[this] (UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle)
		{
			
		}
	);
}
