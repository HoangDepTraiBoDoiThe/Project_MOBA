// Cu Nhat Hoang

#include "AbilityTask_TargetHitResult.h"

#include "Project_MOBA/Character/Player/PlayerCharacter.h"
#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"

UAbilityTask_TargetHitResult* UAbilityTask_TargetHitResult::AbilityTask_TargetHitResult(UGameplayAbility* OwningAbility)
{
	UAbilityTask_TargetHitResult* Obj = NewAbilityTask<UAbilityTask_TargetHitResult>(OwningAbility, FName("UAbilityTask_TargetHitResult"));
	return Obj;
}

void UAbilityTask_TargetHitResult::Activate()
{
	Super::Activate();

	FHitResult HitResult;
	Cast<APlayerCharacter>(GetAvatarActor())->GetMyPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	TargetDataHitResultDelegate.Broadcast(HitResult);
}

void UAbilityTask_TargetHitResult::OnTargetDataHitResultCallback(FHitResult HitResult)
{
	EndTask();
}

void UAbilityTask_TargetHitResult::OnDestroy(bool bInOwnerFinished)
{
	TargetDataHitResultDelegate.Clear();
	
	Super::OnDestroy(bInOwnerFinished);
}
