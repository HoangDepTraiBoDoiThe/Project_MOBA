// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "BaseWidgetController.generated.h"

class UBaseAttributeSet;
class UMyAbilitySystemComponent;
class AMyPlayerState;
/**
 * 
 */
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

UCLASS(Blueprintable, BlueprintType)
class PROJECT_MOBA_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UBaseWidgetController();
	virtual void SetupWidgetController(FWidgetControllerStruct ControllerStruct);

	// Attributes
	UFUNCTION(BlueprintCallable)
	virtual void BroadCastInitialValues() const {}
	
protected:
	FWidgetControllerStruct* WidgetControllerInfos;

};
