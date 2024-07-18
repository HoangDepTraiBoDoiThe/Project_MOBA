// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BTService_Finding.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_MinionSearchForTarget.generated.h"

class AMotherBase;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UBTService_MinionSearchForTarget : public UBTService_Finding
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SetTargetTerritory();

	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector KeySelector_TargetTerritory;

};
