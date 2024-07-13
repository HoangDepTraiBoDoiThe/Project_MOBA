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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayAttributeValuesSignature, const float, NewValue, FGameplayAttribute, Attribute);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCharacterXPToViewSignature, const int32, Loop, const int32, CurrentXP, const int32, XPForCurrentLevel, const int32, XPForNextLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterLevelToViewSignature, const int32, OldLevel, const int32, NewLevel);

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

	// Attributes
	virtual void BroadCastInitialValues() const override;
	
	UPROPERTY(BlueprintAssignable)
	FAbilityPointSpendSignature OnAbilityPointSpendDelegate;
	UPROPERTY(BlueprintAssignable)
	FLevelUpAbleAbilityTagsSignature LevelUpAbleAbilityTagsDelegate;
		
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeValuesSignature OnAttributeValuesSignature;

	// Experience
	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnCharacterXPToViewSignature OnCharacterXPToViewSignature;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnCharacterLevelToViewSignature OnCharacterLevelToViewSignature;
};
