// Cu Nhat Hoang


#include "MainWidgetController.h"

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

void UMainWidgetController::BindReceivedCallBacksToDependencies() const
{
	WidgetControllerInfos->PS->AbilityPointDelegate.BindLambda(
		[this] (const int32 CharacterLevel)
		{
			const TArray<FGameplayTag> Tags = WidgetControllerInfos->ASC->GetLevelUpAbleAbilityTags(CharacterLevel);
			LevelUpAbleAbilityTagsDelegate.Broadcast(Tags);
		}
	);
}

