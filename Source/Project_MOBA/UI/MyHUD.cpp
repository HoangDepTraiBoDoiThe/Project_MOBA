// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

#include "Blueprint/UserWidget.h"
#include "UserWidget/BaseUserWidget.h"
#include "WidgetController/MainWidgetController.h"

void AMyHUD::InitializeUI()
{
	if (MainWidgetClass)
	{
		UBaseUserWidget* UserWidget = CreateWidget<UBaseUserWidget>(GetOwningPlayerController(), MainWidgetClass);
		UserWidget->AddToViewport();
	}
}

UMainWidgetController* AMyHUD::GetMainWidgetController(const FWidgetControllerStruct& WidgetControllerStruct)
{
	if (!MainWidgetController)
	{
		MainWidgetController = NewObject<UMainWidgetController>();
		MainWidgetController->SetupWidgetController(WidgetControllerStruct);
	}
	return MainWidgetController;
}
