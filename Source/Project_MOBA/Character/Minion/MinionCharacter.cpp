// Cu Nhat Hoang


#include "MinionCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Controller/MyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

AMinionCharacter::AMinionCharacter()
{
	MyAbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability system component"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("BaseAttributeSet"));
	MyAbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;
}

void AMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AMinionCharacter::Die()
{
	Cast<AMyAIController>(GetController())->GetBehaviorTreeComponent()->StopLogic("Death");
	Super::Die();
}

AMyAIController* AMinionCharacter::GetMyAIController()
{
	if (!MyAIController) MyAIController = Cast<AMyAIController>(GetInstigatorController());
	return MyAIController;
}

void AMinionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyAbilitySystemComponent->ActorASCInitializeServer(this, this);

	AMyAIController* AIController = Cast<AMyAIController>(NewController);
	if (AIController) AIController->SetupBehavior(BehaviorTree);
}

void AMinionCharacter::OnRep_Controller()
{
	Super::OnRep_Controller();
	MyAbilitySystemComponent->ActorASCInitializeClient();
}
