// Cu Nhat Hoang


#include "MotherBase.h"

#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GameModeBase/MyGameModeBase.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

AMotherBase::AMotherBase()
{
	MyAbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability system component"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("BaseAttributeSet"));
}

void AMotherBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMotherBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	MyAbilitySystemComponent->ActorASCInitialize(this, this);
}

void AMotherBase::Die()
{
	Super::Die();
	
	UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->EndGame();
}

void AMotherBase::BeginPlay()
{
	Super::BeginPlay();

	UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->GetTeamBaseMap().Add(GetTeamTag(), this);
}
