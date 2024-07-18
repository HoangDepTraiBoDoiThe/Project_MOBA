// Cu Nhat Hoang


#include "BTService_Finding.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/Interface/CombatInterface.h"

void UBTService_Finding::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SearchingForTarget();
}

void UBTService_Finding::SearchingForTarget()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(AIOwner->GetPawn());
	const FVector Origin = AIOwner->GetPawn()->GetActorLocation();

	TArray<ICombatInterface*> OutCombatActors;
	ICombatInterface* CombatOwner = Cast<ICombatInterface>(AIOwner->GetPawn());
	const FGameplayTag TeamTag = CombatOwner->GetTeamTag();
	
	UMyBlueprintFunctionLibrary::GetFilteredCombatActorListFromOverlappedActors(GetWorld(), Origin, SearchRadius, ObjectTypeQueries, UCombatInterface::StaticClass(), TeamTag, ActorsToIgnore, OutCombatActors);
	
	for (const FGameplayTag TargetType : TargetActorClassTypes)
	{
		for (ICombatInterface* OverlappedActor : OutCombatActors)
		{
			const FGameplayTag ActorCharacterTag = OverlappedActor->GetActorTag();
			if (!ActorCharacterTag.MatchesTag(TargetType)) continue;
			
			UBTFunctionLibrary::SetBlackboardValueAsObject(this, KeySelector_CurrentTargetActor, Cast<AActor>(OverlappedActor));
			return;
		}
	}
}
