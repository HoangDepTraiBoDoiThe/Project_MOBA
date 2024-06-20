// Cu Nhat Hoang


#include "MinionCharacter.h"

#include "Controller/MyAIController.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

AMinionCharacter::AMinionCharacter()
{
	MyAbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability system component"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("Attribute set"));
	MyAbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;
}

void AMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	MyAbilitySystemComponent->InitAbilityActorInfo(this, this);
	
}

AMyAIController* AMinionCharacter::GetMyAIController()
{
	if (!MyAIController) MyAIController = Cast<AMyAIController>(GetInstigatorController());
	return MyAIController;
}

void AMinionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	GetMyAIController();

	AMyAIController* AIController = Cast<AMyAIController>(NewController);
	if (AIController) AIController->SetupBehavior(BehaviorTree);
}
