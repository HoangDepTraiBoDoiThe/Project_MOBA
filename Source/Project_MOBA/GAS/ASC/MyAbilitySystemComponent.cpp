// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Project_MOBA.h"
#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Data/HeroInfosDataAsset.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GAS/GameplayAbility/BaseGameplayAbility.h"

void UMyAbilitySystemComponent::PlayerASCInitialize(AActor* InOwnerActor, AActor* InAvatarActor)
{
	InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	ApplyDefaultGEs();
	GiveStartupAbilities();

	TArray<FGameplayAttribute> Attributes;
	GetAllAttributes(Attributes);
	for (const FGameplayAttribute& Attribute : Attributes)
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

bool UMyAbilitySystemComponent::TryActivateAbilityByInputTag(const FGameplayTag InputTag)
{
	
	for (auto& Ability : GetActivatableAbilities())
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
	GetPlayerCharacter()->GetHeroInfosDataAsset()->GetDefaultGEs(PlayerCharacter->GetHeroTag(), PrimaryGE, SecondaryGEs);
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
	for (auto& AbilityClass : *GetPlayerCharacter()->GetHeroStartupAbilities())
	{
		FGameplayAbilitySpec Ability = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbility(Ability);
	}
}

APlayerCharacter* UMyAbilitySystemComponent::GetPlayerCharacter()
{
	if (!PlayerCharacter) PlayerCharacter = Cast<APlayerCharacter>(GetAvatarActor());
	return PlayerCharacter;
}
