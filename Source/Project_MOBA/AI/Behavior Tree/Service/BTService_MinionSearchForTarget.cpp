 // Cu Nhat Hoang


#include "BTService_MinionSearchForTarget.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Project_MOBA/Character/Minion/MinionCharacter.h"

void UBTService_MinionSearchForTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	SetTargetTerritory();
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

 void UBTService_MinionSearchForTarget::SetTargetTerritory()
 {
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, KeySelector_TargetTerritory, Cast<AActor>(Cast<AMinionCharacter>(AIOwner->GetPawn<AMinionCharacter>())->GetOpponentMotherBase()));
 }
