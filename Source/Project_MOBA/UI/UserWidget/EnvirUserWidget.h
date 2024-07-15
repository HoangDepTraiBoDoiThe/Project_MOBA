// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "EnvirUserWidget.generated.h"

class UEnvironmentWidgetController;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UEnvirUserWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	void SetWidgetController(UEnvironmentWidgetController* WidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();

protected:
	UPROPERTY(BlueprintReadOnly)
	UEnvironmentWidgetController* EnvironmentWidgetController;
	
};
