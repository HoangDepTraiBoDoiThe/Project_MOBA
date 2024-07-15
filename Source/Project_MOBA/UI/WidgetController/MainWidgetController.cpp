// Cu Nhat Hoang


#include "MainWidgetController.h"

#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"
#include "Project_MOBA/UI/MyHUD.h"

UMainWidgetController::UMainWidgetController()
{
	WidgetControllerInfos = nullptr;
}

void UMainWidgetController::SetupWidgetController(FWidgetControllerStruct ControllerStruct)
{
	WidgetControllerInfos = new FWidgetControllerStruct(ControllerStruct.PC, ControllerStruct.PS, ControllerStruct.ASC, ControllerStruct.AS);

	BindReceivedCallBacksToDependencies();
}

void UMainWidgetController::UpgradeAbility(const FGameplayTag& AbilityTag)
{
	WidgetControllerInfos->ASC->Server_LevelUpAbility(AbilityTag, WidgetControllerInfos->PS->GetPlayerLevel());
	OnAbilityUpgradeDelegate.Broadcast(AbilityTag);
}

void UMainWidgetController::BroadCastInitialValues() const
{
	check (WidgetControllerInfos->AS)
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetHitPoint(), WidgetControllerInfos->AS->GetHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetMaxHitPoint(), WidgetControllerInfos->AS->GetMaxHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetMana(), WidgetControllerInfos->AS->GetManaAttribute());
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetMaxMana(), WidgetControllerInfos->AS->GetMaxManaAttribute());
}

void UMainWidgetController::BindReceivedCallBacksToDependencies()
{
	WidgetControllerInfos->ASC->OnNewAttributeValueBroadcastToControllerDelegate.AddLambda(
		[this] (const FOnAttributeChangeData& AttributeChangeData)
		{
			OnAttributeValuesSignature.Broadcast(AttributeChangeData.NewValue, AttributeChangeData.Attribute);
		});
	WidgetControllerInfos->PS->AbilityPointDelegate.BindLambda(
		[this] (const int32 CharacterLevel)
		{
			const FGameplayTagContainer Tags = WidgetControllerInfos->ASC->GetLevelUpAbleAbilityTags(CharacterLevel);
			LevelUpAbleAbilityTagsDelegate.Broadcast(Tags);
		}
	);
	WidgetControllerInfos->PS->OnXPChangeDelegate.AddLambda(
		[this] (const int32 NewValue, const int32 OldValue)
	{
		int32 Loop;
		int32 XPForCurrentLevel;
		int32 XPForNextLevel;
		WidgetControllerInfos->PC->GetPlayerCharacter()->GetCharacterInfosDataAsset()->GetXPInfos(NewValue, OldValue, Loop, XPForCurrentLevel, XPForNextLevel);
		OnCharacterXPToViewSignature.Broadcast(Loop, NewValue, XPForCurrentLevel, XPForNextLevel);
	});
	WidgetControllerInfos->PS->OnLevelChangeDelegate.AddLambda(
		[this] (const int32 NewValue, const int32 OldValue)
	{
		OnCharacterLevelToViewSignature.Broadcast(OldValue, NewValue);
	});
	WidgetControllerInfos->ASC->OnGameplayAbilityStatusToControllerDelegate.AddLambda(
		[this] (const FGameplayTag AbilityTag, const FGameplayTag AbilityState, const int32 AbilityLevel)
		{
			const FHeroUIDataStruct HeroUIDataData = GetHeroUIDataAsset()->GetUIDataByHeroTag(WidgetControllerInfos->PS->GetPlayerCharacter()->GetCharacterTag());
			for (auto Struct : HeroUIDataData.AbilityUIData)
			{
				if (Struct.AbilityTag.MatchesTagExact(AbilityTag))
				{
					Struct.AbilityState = AbilityState;
					Struct.AbilityLevel = AbilityLevel;
					OnAbilityUpdateToViewDelegate.Broadcast(Struct);
					break;
				}
			}
		});

	BroadCastInitialValues();
}

void UMainWidgetController::BroadCastCurrentAttributes()
{
	TArray<FGameplayAttribute> Attributes;
	WidgetControllerInfos->ASC->GetAllAttributes(Attributes);
	for (const FGameplayAttribute& Attribute : Attributes)
	{
		OnAttributeValuesSignature.Broadcast(Attribute.GetNumericValue(WidgetControllerInfos->AS), Attribute);
	}
}

void UMainWidgetController::RequestAbilityInitialUIData()
{
	const FHeroUIDataStruct HeroUIDataData = GetHeroUIDataAsset()->GetUIDataByHeroTag(WidgetControllerInfos->PS->GetPlayerCharacter()->GetCharacterTag());
	for (auto Struct : HeroUIDataData.AbilityUIData)
	{
		Struct.AbilityState = MyGameplayTagsManager::Get().Ability_Availability_Unlockable;
		OnAbilityUpdateToViewDelegate.Broadcast(Struct);
	}
}

void UMainWidgetController::RequestAbilityUIDataToView()
{
	WidgetControllerInfos->ASC->BroadCastActivatableAbilityUIData();
}

UHeroUIDataAsset* UMainWidgetController::GetHeroUIDataAsset()
{
	if (!HeroUIDataAsset) HeroUIDataAsset = Cast<AMyHUD>(WidgetControllerInfos->PC->GetHUD())->GetHeroUIDataAsset();
	return HeroUIDataAsset;
}

