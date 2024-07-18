// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.h"
#include "Project_MOBA/Data/HeroUIDataAsset.h"
#include "MainWidgetController.generated.h"

class AMyPlayerController;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLevelUpAbleAbilityTagsSignature, const FGameplayTagContainer&, LevelUpAbleAbilityTags);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityPointSpendSignature, FGameplayTag, AbilityTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayAttributeValuesSignature, const float, NewValue, const FGameplayAttribute&, Attribute);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnCharacterXPToViewSignature, const int32, Loop, const int32, CurrentXP, const int32, XPForCurrentLevel, const int32, XPForNextLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterLevelToViewSignature, const int32, OldLevel, const int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityUpdateToViewSignature, const FAbilityUIStruct&, HeroUIDataStruct);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNotifyAbilityLevelUpToViewSignature, FGameplayTag, AbilityTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FNotifyEndingGameToView, const FGameplayTag, TeamWinner, const float, TotalTime);

USTRUCT(BlueprintType)
struct FWidgetControllerStruct
{
	GENERATED_BODY()

	FWidgetControllerStruct(){}
	FWidgetControllerStruct(AMyPlayerController* PC, AMyPlayerState* PS, UMyAbilitySystemComponent* ASC, UBaseAttributeSet* AS)
		: PC(PC), PS(PS), ASC(ASC), AS(AS) {}
	
	UPROPERTY()
	TObjectPtr<AMyPlayerController> PC = nullptr;
	UPROPERTY()
	TObjectPtr<AMyPlayerState> PS = nullptr;
	UPROPERTY()
	TObjectPtr<UMyAbilitySystemComponent> ASC = nullptr;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AS = nullptr;
	
};

UCLASS()
class PROJECT_MOBA_API UMainWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	UMainWidgetController();
	void BindReceivedCallBacksToDependencies();
	virtual void SetupWidgetController(FWidgetControllerStruct ControllerStruct);

	UFUNCTION(BlueprintCallable)
	void UpgradeAbility(const FGameplayTag& AbilityTag);


	FWidgetControllerStruct* GetWidgetControllerInfos() const {return WidgetControllerInfos;}
	
	// Attributes
	virtual void BroadCastInitialValues() const override;

	UFUNCTION(BlueprintCallable)
	void BroadCastCurrentAttributes();
	UFUNCTION(BlueprintCallable)
	void RequestAbilityInitialUIData();
	UFUNCTION(BlueprintCallable)
	void RequestAbilityUIDataToView();

	// Experience
	UPROPERTY(BlueprintAssignable)
	FLevelUpAbleAbilityTagsSignature LevelUpAbleAbilityTagsDelegate;
		
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnGameplayAttributeValuesSignature OnAttributeValuesSignature;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Experience")
	FOnCharacterXPToViewSignature OnCharacterXPToViewSignature;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Experience")
	FOnCharacterLevelToViewSignature OnCharacterLevelToViewSignature;

	// Abilities
	UHeroUIDataAsset* GetHeroUIDataAsset();

	UPROPERTY(BlueprintAssignable, Category = "GAS|Ability")
	FOnAbilityUpdateToViewSignature OnAbilityUpdateToViewDelegate;
	UPROPERTY(BlueprintAssignable, Category = "GAS|Ability")
	FNotifyAbilityLevelUpToViewSignature OnAbilityUpgradeDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|EndGame")
	FNotifyEndingGameToView NotifyEndingGameToView;
	
private:
	FWidgetControllerStruct* WidgetControllerInfos;
	UPROPERTY()
	UHeroUIDataAsset* HeroUIDataAsset;
};
