// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_Finding.generated.h"

/**
 * 
 */ 
UCLASS()
class PROJECT_MOBA_API UBTService_Finding : public UBTService_BlueprintBase
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	void SearchingForTarget();
	
	UPROPERTY(EditInstanceOnly)
	FBlackboardKeySelector KeySelector_CurrentTargetActor;

	// Order matter
	UPROPERTY(EditAnywhere)
	TArray<FGameplayTag> TargetActorClassTypes;
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueries;
	
	UPROPERTY(EditAnywhere)
	float SearchRadius;
	
};
