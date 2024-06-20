// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TargetHitResult.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataHitResultSignature, FGameplayAbilityTargetDataHandle, HitResult);

UCLASS()
class PROJECT_MOBA_API UAbilityTask_TargetHitResult : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintInternalUseOnly, meta=(DefaultToSelf = "OwningAbility", HidePin = "OwningAbility", BlueprintInternalUseOnly="TRUE"), BlueprintCallable)
	static UAbilityTask_TargetHitResult* AbilityTask_TargetHitResult(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FTargetDataHitResultSignature TargetDataHitResultDelegate;

protected:
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

	void StartSendingTargetDataToServer();
	void TargetDataCallBack(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag Tag);
	
	UFUNCTION()
	void OnTargetDataHitResultCallback(FHitResult HitResult);

private:
	FDelegateHandle TargetDataCallBackDelegateHandle;
	
};
