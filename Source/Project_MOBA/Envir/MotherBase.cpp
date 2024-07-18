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

	if (HasAuthority())
	{
		FGameplayTag TeamWinner = GetTeamTag().MatchesTagExact(MyGameplayTagsManager::Get().Team_White) ? MyGameplayTagsManager::Get().Team_Black : MyGameplayTagsManager::Get().Team_White;
		UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->EndGame(TeamWinner);
	}
}

void AMotherBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->GetTeamBaseMap().Add(GetTeamTag(), this);
}

void AMotherBase::Destroyed()
{
	Super::Destroyed();
}
