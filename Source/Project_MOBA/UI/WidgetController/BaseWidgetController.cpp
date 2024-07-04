// Cu Nhat Hoang


#include "BaseWidgetController.h"

UBaseWidgetController::UBaseWidgetController()
{
	WidgetControllerInfos = nullptr;
}

void UBaseWidgetController::SetupWidgetController(FWidgetControllerStruct ControllerStruct)
{
	WidgetControllerInfos = new FWidgetControllerStruct(ControllerStruct.PC, ControllerStruct.PS,
													ControllerStruct.ASC, ControllerStruct.AS);
	
}

