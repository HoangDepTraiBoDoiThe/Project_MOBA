// Cu Nhat Hoang


#include "EnvironmentWidgetController.h"

#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

UEnvironmentWidgetController::UEnvironmentWidgetController(UMyAbilitySystemComponent* ASC, UBaseAttributeSet* AS)
{
	AbilitySystemComponent = ASC;
	BaseAttributeSet = AS;
}

void UEnvironmentWidgetController::SetupWidgetController(UMyAbilitySystemComponent* ASC, UBaseAttributeSet* AS)
{
	AbilitySystemComponent = ASC;
	BaseAttributeSet = AS;

	BindCallBackAndBroadCastToDependencies();
}

void UEnvironmentWidgetController::BindCallBackAndBroadCastToDependencies()
{
	TArray<FGameplayAttribute> OutAttribute;
	AbilitySystemComponent->GetAllAttributes(OutAttribute);
	for (const auto& Attribute : OutAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
			[this](const FOnAttributeChangeData& AttributeChangeData)
			{
				AttributeToViewSignature.Broadcast(AttributeChangeData.Attribute, AttributeChangeData.NewValue);
			});
	}
}

void UEnvironmentWidgetController::BroadCastInitialValues() const
{
	check (BaseAttributeSet)
	AttributeToViewSignature.Broadcast(BaseAttributeSet->GetHitPointAttribute(), BaseAttributeSet->GetHitPoint());
	AttributeToViewSignature.Broadcast(BaseAttributeSet->GetMaxHitPointAttribute(),BaseAttributeSet->GetMaxHitPoint());
	AttributeToViewSignature.Broadcast(BaseAttributeSet->GetManaAttribute(), BaseAttributeSet->GetMana());
	AttributeToViewSignature.Broadcast(BaseAttributeSet->GetMaxManaAttribute(), BaseAttributeSet->GetMaxMana());

}
