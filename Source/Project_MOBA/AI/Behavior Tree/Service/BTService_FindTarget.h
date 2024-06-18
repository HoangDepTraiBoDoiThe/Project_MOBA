// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UBTService_FindTarget : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActor;
		
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries;
	
	UPROPERTY(EditAnywhere)
	float SearchRadius;	
};
