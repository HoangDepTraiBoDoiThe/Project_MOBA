// Cu Nhat Hoang


#include "BTService_FindTarget.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Interface/AttackableInterface.h"

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.AddUnique(AIOwner->GetPawn());
	const FVector Origin = AIOwner->GetPawn()->GetActorLocation();

	FCollisionQueryParams SphereParams(SCENE_QUERY_STAT(ApplyRadialDamage),  false, AIOwner);
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	// query scene to see what we hit
	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(GetWorld(), EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects), FCollisionShape::MakeSphere(SearchRadius), SphereParams);
	}
	UKismetSystemLibrary::DrawDebugCapsule(GetWorld(), Origin, SearchRadius, SearchRadius, FRotator());

	for (FOverlapResult& Actor : Overlaps)
	{
		if (Actor.GetActor()->Implements<UAttackableInterface>())
		{
			UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetActor, Actor.GetActor());
		}
	}
}
