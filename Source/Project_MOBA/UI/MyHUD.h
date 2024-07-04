// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UBaseUserWidget;
struct FWidgetControllerStruct;
class UMainWidgetController;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitializeUI();
	UMainWidgetController* GetMainWidgetController(const FWidgetControllerStruct& WidgetControllerStruct);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainWidgetClass;
	
private:
	UPROPERTY()
	UMainWidgetController* MainWidgetController; 
	
};
