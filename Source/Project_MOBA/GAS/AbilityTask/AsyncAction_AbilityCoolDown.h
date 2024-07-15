// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncAction_AbilityCoolDown.generated.h"

struct FGameplayTag;
class UGameplayAbility;
class UMyAbilitySystemComponent;
class UBaseGameplayAbility;
class UMainWidgetController;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityCoolDownTimeRemaining, float, TimeRemaining);

UCLASS(BlueprintType, meta=(ExposedAsyncProxy="AsyncTask"))
class PROJECT_MOBA_API UAsyncAction_AbilityCoolDown : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UAsyncAction_AbilityCoolDown();
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "TRUE"))
	static UAsyncAction_AbilityCoolDown* WaitAbilityCoolDown(const UMainWidgetController* MainWidgetController, FGameplayTag AbilityTag);

	UPROPERTY(BlueprintAssignable)
	FAbilityCoolDownTimeRemaining AbilityCoolDownTimeRemainingDelegate;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetReadyToDestroy() override;

protected:
	void OnAbilityCommitted(UGameplayAbility* GameplayAbility) const;
	TObjectPtr<UMyAbilitySystemComponent> OwningASC;

	FGameplayTag OwningAbilityTag;
};
