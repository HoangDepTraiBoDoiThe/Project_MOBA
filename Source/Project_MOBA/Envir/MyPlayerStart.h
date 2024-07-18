// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerStart.h"
#include "MyPlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMyPlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	FGameplayTag GetTeamTag() const {return TeamTag;}

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag TeamTag;
	
};
