// Cu Nhat Hoang


#include "MyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Project_MOBA/Character/Minion/MinionCharacter.h"

AMyAIController::AMyAIController()
{
	BTComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("Behavior Tree Coponent"));
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetMinionCharacter())
	{
		RunBehaviorTree(MinionCharacter->GetMinionBehaviorTree());
		Blackboard->InitializeBlackboard(*MinionCharacter->GetMinionBehaviorTree()->GetBlackboardAsset());
	}
}

AMinionCharacter* AMyAIController::GetMinionCharacter()
{
	if (!MinionCharacter) MinionCharacter = Cast<AMinionCharacter>(GetPawn());
	return MinionCharacter;
}
