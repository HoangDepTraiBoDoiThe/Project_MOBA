// Cu Nhat Hoang


#include "AsyncAction_AbilityCoolDown.h"

#include "Project_MOBA/GAS/GameplayAbility/BaseGameplayAbility.h"
#include "Project_MOBA/UI/WidgetController/MainWidgetController.h"

UAsyncAction_AbilityCoolDown::UAsyncAction_AbilityCoolDown()
{
}

UAsyncAction_AbilityCoolDown* UAsyncAction_AbilityCoolDown::WaitAbilityCoolDown(
	const UMainWidgetController* MainWidgetController, FGameplayTag AbilityTag)
{
	UAsyncAction_AbilityCoolDown* Obj = NewObject<UAsyncAction_AbilityCoolDown>();
	Obj->OwningASC = MainWidgetController->GetWidgetControllerInfos()->ASC;
	Obj->OwningAbilityTag = AbilityTag;
	Obj->OwningASC->AbilityCommittedCallbacks.AddUObject(Obj, &ThisClass::OnAbilityCommitted);
	return Obj;
}

void UAsyncAction_AbilityCoolDown::SetReadyToDestroy()
{
	AbilityCoolDownTimeRemainingDelegate.Clear();
	Super::SetReadyToDestroy();
}

void UAsyncAction_AbilityCoolDown::OnAbilityCommitted(UGameplayAbility* GameplayAbility) const
{
	if (Cast<UBaseGameplayAbility>(GameplayAbility)->GetAbilityTag().MatchesTagExact(OwningAbilityTag))
	{
		const float TimeRemaining = GameplayAbility->GetCooldownTimeRemaining();
		AbilityCoolDownTimeRemainingDelegate.Broadcast(TimeRemaining);
	}
}
