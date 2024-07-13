// Cu Nhat Hoang


#include "MainWidgetController.h"

#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

UMainWidgetController::UMainWidgetController()
{
}

void UMainWidgetController::SetupWidgetController(FWidgetControllerStruct ControllerStruct)
{
	Super::SetupWidgetController(ControllerStruct);

	BindReceivedCallBacksToDependencies();
}

void UMainWidgetController::UpgradeAbility(const FGameplayTag& AbilityTag)
{
	WidgetControllerInfos->ASC->Server_LevelUpAbility(AbilityTag, WidgetControllerInfos->PS->GetPlayerLevel());
	OnAbilityPointSpendDelegate.Broadcast(AbilityTag);
}

void UMainWidgetController::BroadCastInitialValues() const
{
	check (WidgetControllerInfos->AS)
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetHitPoint(), WidgetControllerInfos->AS->GetHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetMaxHitPoint(), WidgetControllerInfos->AS->GetMaxHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetMana(), WidgetControllerInfos->AS->GetManaAttribute());
	OnAttributeValuesSignature.Broadcast(WidgetControllerInfos->AS->GetMaxMana(), WidgetControllerInfos->AS->GetMaxManaAttribute());
}

void UMainWidgetController::BindReceivedCallBacksToDependencies() const
{
	WidgetControllerInfos->ASC->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddLambda(
		[this] (const FOnAttributeChangeData& AttributeChangeData)
		{
			OnAttributeValuesSignature.Broadcast(AttributeChangeData.NewValue, AttributeChangeData.Attribute);
		});
	WidgetControllerInfos->PS->AbilityPointDelegate.BindLambda(
		[this] (const int32 CharacterLevel)
		{
			const TArray<FGameplayTag> Tags = WidgetControllerInfos->ASC->GetLevelUpAbleAbilityTags(CharacterLevel);
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

	BroadCastInitialValues();
}

