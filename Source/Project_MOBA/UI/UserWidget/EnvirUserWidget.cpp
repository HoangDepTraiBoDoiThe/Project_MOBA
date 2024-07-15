// Cu Nhat Hoang


#include "EnvirUserWidget.h"

void UEnvirUserWidget::SetWidgetController(UEnvironmentWidgetController* WidgetController)
{
	EnvironmentWidgetController = WidgetController;
	OnWidgetControllerSet();
}
