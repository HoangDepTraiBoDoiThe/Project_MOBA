// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnvironmentInterface.generated.h"

class UWidgetComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnvironmentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_MOBA_API IEnvironmentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UMyAbilitySystemComponent* GetASC() = 0;
	virtual UBaseAttributeSet* GetAS() = 0;
	virtual UWidgetComponent* GetWidgetComponent() = 0;
};
