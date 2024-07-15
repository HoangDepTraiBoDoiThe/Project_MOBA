// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseWidgetController.h"
#include "EnvironmentWidgetController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeToViewSignature, FGameplayAttribute, Attribute, float, Value);

UCLASS()
class PROJECT_MOBA_API UEnvironmentWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	UEnvironmentWidgetController() {}
	UEnvironmentWidgetController(UMyAbilitySystemComponent* AbilitySystemComponent, UBaseAttributeSet* AS);
	void SetupWidgetController(UMyAbilitySystemComponent* AbilitySystemComponent, UBaseAttributeSet* AS);

	void BindCallBackAndBroadCastToDependencies();
	virtual void BroadCastInitialValues() const override;

	UPROPERTY(BlueprintAssignable)
	FAttributeToViewSignature AttributeToViewSignature;
	
protected:
	UPROPERTY()
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;
	
};
