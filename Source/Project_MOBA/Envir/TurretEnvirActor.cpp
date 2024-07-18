// Cu Nhat Hoang


#include "TurretEnvirActor.h"

#include "Components/SphereComponent.h"
#include "Project_MOBA/Character/Minion/Controller/MyAIController.h"
#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"

ATurretEnvirActor::ATurretEnvirActor()
{
	AttackingRangeComponent = CreateDefaultSubobject<USphereComponent>("Attacking range component");
	AttackingRangeComponent->SetupAttachment(GetRootComponent());
}

UPrimitiveComponent* ATurretEnvirActor::GetAttackableActor_Mesh()
{
	return GetMesh();
}

ABaseCharacter* ATurretEnvirActor::GetTargetActor()
{
	return Cast<ABaseCharacter>(TargetActor);
}

void ATurretEnvirActor::BeginPlay()
{
	Super::BeginPlay();
	AttackingRangeComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOpponentEnteringAttackingBoundary);
}

void ATurretEnvirActor::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	Cast<AMyAIController>(NewController)->SetupBehavior(BehaviorTree);
}

void ATurretEnvirActor::OnOpponentEnteringAttackingBoundary(UPrimitiveComponent* OverlappedComponent,
                                                            AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                            const FHitResult& SweepResult)
{
 	if (!GetTeamTag().MatchesTagExact(Cast<ABaseCharacter>(OtherActor)->GetTeamTag()))
	{
	}
}
