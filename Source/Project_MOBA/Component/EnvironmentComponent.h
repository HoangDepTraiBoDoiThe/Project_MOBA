// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnvironmentComponent.generated.h"

class UWidgetComponent;
class IEnvironmentInterface;
class UBaseUserWidget;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FEnvirWidgetControllerStruct
{
	GENERATED_BODY()

	FEnvirWidgetControllerStruct(){}
	FEnvirWidgetControllerStruct(UMyAbilitySystemComponent* ASC, UBaseAttributeSet* AS)
		: ASC(ASC), AS(AS) {}
	
	UPROPERTY()
	TObjectPtr<UMyAbilitySystemComponent> ASC = nullptr;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AS = nullptr;
	
};

class UEnvironmentWidgetController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MOBA_API UEnvironmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	friend class AMinionCharacter;
	UEnvironmentComponent();
	void SetWidgetControllerToWidget();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	IEnvironmentInterface* GetEnvirCompOwner();

	UEnvironmentWidgetController* GetEnvironmentWidgetController(FEnvirWidgetControllerStruct EnvirWidgetControllerStruct);

protected:
	virtual void BeginPlay() override;
	IEnvironmentInterface* Owner;

private:
	UPROPERTY()
	UEnvironmentWidgetController* EnvironmentWidgetController;
	
};
