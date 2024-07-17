// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnvironmentComponent.generated.h"

class ABaseCharacter;
class ICombatInterface;
class UWidgetComponent;
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
	ABaseCharacter* GetEnvirCompOwner();

	UEnvironmentWidgetController* GetEnvironmentWidgetController(FEnvirWidgetControllerStruct EnvirWidgetControllerStruct);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	ABaseCharacter* EnvirComponentOwner;

private:
	UPROPERTY()
	UEnvironmentWidgetController* EnvironmentWidgetController;
	
};
