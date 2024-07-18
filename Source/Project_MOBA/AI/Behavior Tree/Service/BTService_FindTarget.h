// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindTarget.generated.h"

class AMotherBase;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UBTService_FindTarget : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SetTargetTerritory();

	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector KeySelector_CurrentTargetActor;
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector KeySelector_TargetTerritory;

	// Order matter
	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> TargetActorClassTypes;
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries;
	
	UPROPERTY(EditAnywhere)
	float SearchRadius;	
};
