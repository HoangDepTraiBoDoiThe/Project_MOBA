// Cu Nhat Hoang


#include "MotherBase.h"

#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GameModeBase/MyGameModeBase.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"

AMotherBase::AMotherBase()
{
}

void AMotherBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
