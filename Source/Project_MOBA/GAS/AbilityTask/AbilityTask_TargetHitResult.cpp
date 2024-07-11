// Cu Nhat Hoang

#include "AbilityTask_TargetHitResult.h"

#include "AbilitySystemComponent.h"
#include "Project_MOBA/Project_MOBA.h"
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

	if (GetAvatarActor()->GetInstigatorController()->IsLocalController())
	{
		StartSendingTargetDataToServer();
	}
	else
	{
		TargetDataCallBackDelegateHandle = AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &ThisClass::TargetDataCallBack);
		if (!AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey()))
			SetWaitingOnRemotePlayerData();
	}
}

void UAbilityTask_TargetHitResult::StartSendingTargetDataToServer()
{
	FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get());
	
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> Objects;
	Objects.AddUnique(EOTQ_GroundObject);
	Objects.AddUnique(EOTQ_TurretObject);
	Objects.AddUnique(EOTQ_CharacterObject);
	Cast<APlayerCharacter>(GetAvatarActor())->GetMyPlayerController()->GetHitResultUnderCursorForObjects(Objects, false, HitResult);
	FGameplayAbilityTargetData_SingleTargetHit* TargetData_Cursor = new FGameplayAbilityTargetData_SingleTargetHit();
	TargetData_Cursor->HitResult = HitResult;
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle.Add(TargetData_Cursor);
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), TargetDataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);
	
	TargetDataCallBack(TargetDataHandle, FGameplayTag());
}

void UAbilityTask_TargetHitResult::TargetDataCallBack(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag Tag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(Ability->GetCurrentAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates()) TargetDataHitResultDelegate.Broadcast(TargetDataHandle);
}

void UAbilityTask_TargetHitResult::OnTargetDataHitResultCallback(FHitResult HitResult)
{
	EndTask();
}

void UAbilityTask_TargetHitResult::OnDestroy(bool bInOwnerFinished)
{
	TargetDataHitResultDelegate.Clear();
	if (TargetDataCallBackDelegateHandle.IsValid())
		AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).Remove(TargetDataCallBackDelegateHandle);
	
	Super::OnDestroy(bInOwnerFinished);
}
