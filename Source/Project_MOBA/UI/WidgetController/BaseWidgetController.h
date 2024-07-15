// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseWidgetController.generated.h"

class UBaseAttributeSet;
class UMyAbilitySystemComponent;
class AMyPlayerState;
/**
 * 
 */


UCLASS(Blueprintable, BlueprintType)
class PROJECT_MOBA_API UBaseWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void BroadCastInitialValues() const;
	
protected:

};
