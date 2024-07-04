// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "MainWidgetController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelUpAbleAbilityTagsSignature, const TArray<FGameplayTag>&, LevelUpAbleAbilityTags);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityPointSpendSignature, FGameplayTag, AbilityTag);

UCLASS()
class PROJECT_MOBA_API UMainWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	UMainWidgetController();
	void BindReceivedCallBacksToDependencies() const;
	virtual void SetupWidgetController(FWidgetControllerStruct ControllerStruct) override;

	UFUNCTION(BlueprintCallable)
	void UpgradeAbility(const FGameplayTag& AbilityTag);

	UPROPERTY(BlueprintAssignable)
	FAbilityPointSpendSignature OnAbilityPointSpendDelegate;
	UPROPERTY(BlueprintAssignable)
	FLevelUpAbleAbilityTagsSignature LevelUpAbleAbilityTagsDelegate;
};
