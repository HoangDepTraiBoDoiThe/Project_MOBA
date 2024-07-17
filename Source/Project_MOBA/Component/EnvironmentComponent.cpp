// Cu Nhat Hoang


#include "EnvironmentComponent.h"

#include "Components/WidgetComponent.h"
#include "Project_MOBA/Interface/EnvironmentInterface.h"
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
	const FEnvirWidgetControllerStruct EnvirWidgetControllerStruct(GetEnvirCompOwner()->GetASC(), GetEnvirCompOwner()->GetAS());
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

IEnvironmentInterface* UEnvironmentComponent::GetEnvirCompOwner()
{
	if (!Owner) Owner = Cast<IEnvironmentInterface>(GetOwner());
	return Owner;
}

