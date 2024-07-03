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

	MyAbilitySystemComponent->ActorASCInitialize(this, this);

	AMyAIController* AIController = Cast<AMyAIController>(NewController);
	if (AIController) AIController->SetupBehavior(BehaviorTree);
}

void AMinionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMinionCharacter::IncreaseXP2Give(const int32 XPAmount)
{
	XP2Give += XPAmount;
}

int32 AMinionCharacter::GetXP()
{
	return XP;
}

int32 AMinionCharacter::GetXPReward()
{
	return XP2Give;
}

void AMinionCharacter::Destroyed()
{
	TArray<TObjectPtr<UParticleSystem>> OutParticleSystems;
	CharacterInfos->GetParticleSystems(GetCharacterTag(), OutParticleSystems);
	for (const auto& Item : OutParticleSystems)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Item, GetActorTransform());
	}
	
	Super::Destroyed();
}
