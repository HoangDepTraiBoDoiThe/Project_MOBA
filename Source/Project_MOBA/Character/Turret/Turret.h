// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API ATurret : public ABaseCharacter
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
};
