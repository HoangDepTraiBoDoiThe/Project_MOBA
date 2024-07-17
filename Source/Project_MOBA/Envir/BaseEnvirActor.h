// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "BaseEnvirActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API ABaseEnvirActor : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseEnvirActor();

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	
};
