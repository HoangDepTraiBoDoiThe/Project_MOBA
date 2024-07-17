// Cu Nhat Hoang


#include "EnvironmentComponent.h"

#include "Components/WidgetComponent.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "Project_MOBA/UI/UserWidget/EnvirUserWidget.h"
#include "Project_MOBA/UI/WidgetController/EnvironmentWidgetController.h"

UEnvironmentComponent::UEnvironmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UEnvironmentComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UEnvironmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UEnvironmentComponent::SetWidgetControllerToWidget()
{
	const FEnvirWidgetControllerStruct EnvirWidgetControllerStruct(GetEnvirCompOwner()->GetMyAbilitySystemComponent(), GetEnvirCompOwner()->GetBaseAttributeSet());
	if (GetEnvirCompOwner()->GetWidgetComponent()->GetWidget())
		Cast<UEnvirUserWidget>(GetEnvirCompOwner()->GetWidgetComponent()->GetWidget())->SetWidgetController(GetEnvironmentWidgetController(EnvirWidgetControllerStruct));
}

UEnvironmentWidgetController* UEnvironmentComponent::GetEnvironmentWidgetController(
	FEnvirWidgetControllerStruct EnvirWidgetControllerStruct)
{
	if (!EnvironmentWidgetController)
	{
		EnvironmentWidgetController = NewObject<UEnvironmentWidgetController>();
		EnvironmentWidgetController->SetupWidgetController(EnvirWidgetControllerStruct.ASC, EnvirWidgetControllerStruct.AS);
	}
	return EnvironmentWidgetController;
}

ABaseCharacter* UEnvironmentComponent::GetEnvirCompOwner()
{
	if (!Owner) Owner = Cast<ABaseCharacter>(GetOwner());
	return Owner;
}

