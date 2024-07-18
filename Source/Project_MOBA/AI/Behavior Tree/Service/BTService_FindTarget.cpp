 // Cu Nhat Hoang


#include "BTService_FindTarget.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Project_MOBA/Character/Minion/MinionCharacter.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/Interface/CombatInterface.h"

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	SetTargetTerritory();
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(AIOwner->GetPawn());
	const FVector Origin = AIOwner->GetPawn()->GetActorLocation();

	TArray<ICombatInterface*> OutCombatActors;
	ICombatInterface* CombatOwner = Cast<ICombatInterface>(AIOwner->GetPawn());
	const FGameplayTag TeamTag = CombatOwner->GetTeamTag();
	
	UMyBlueprintFunctionLibrary::GetFilteredCombatActorListFromOverlappedActors(GetWorld(), Origin, SearchRadius, ObjectTypeQueries, UCombatInterface::StaticClass(), TeamTag, ActorsToIgnore, OutCombatActors);
	/*
	UKismetSystemLibrary::DrawDebugCapsule(GetWorld(), Origin, SearchRadius, SearchRadius, FRotator());
	*/
	
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

 void UBTService_FindTarget::SetTargetTerritory()
 {
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, KeySelector_TargetTerritory, Cast<AActor>(Cast<AMinionCharacter>(AIOwner->GetPawn<AMinionCharacter>())->GetOpponentMotherBase()));
 }
