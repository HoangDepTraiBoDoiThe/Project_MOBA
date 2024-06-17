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
		
	}
}

AMinionCharacter* AMyAIController::GetMinionCharacter()
{
	if (!MinionCharacter) MinionCharacter = Cast<AMinionCharacter>(GetPawn());
	return MinionCharacter;
}

void AMyAIController::SetupBehavior(UBehaviorTree* BehaviorTree)
{
	RunBehaviorTree(BehaviorTree);
	Blackboard->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
}
