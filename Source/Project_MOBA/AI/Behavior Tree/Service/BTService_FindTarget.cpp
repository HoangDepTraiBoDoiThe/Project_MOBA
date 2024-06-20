// Cu Nhat Hoang


#include "BTService_FindTarget.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/Interface/AttackableInterface.h"

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(AIOwner->GetPawn());
	const FVector Origin = AIOwner->GetPawn()->GetActorLocation();

	TArray<AActor*> OutActors;
	UMyBlueprintFunctionLibrary::GetFilteredActorListFromComponentList(GetWorld(), Origin, SearchRadius, ObjectTypeQueries, UAttackableInterface::StaticClass(), ActorsToIgnore, OutActors);
	/*
	UKismetSystemLibrary::DrawDebugCapsule(GetWorld(), Origin, SearchRadius, SearchRadius, FRotator());
	*/

	for (AActor* Actor : OutActors)
	{
		if (Actor->Implements<UAttackableInterface>())
		{
			UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetActor, Actor);
			return;
		}
		UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetActor, nullptr);
	}
}