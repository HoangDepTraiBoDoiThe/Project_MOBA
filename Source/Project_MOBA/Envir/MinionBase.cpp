// Cu Nhat Hoang


#include "MinionBase.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Project_MOBA/Character/Minion/MinionCharacter.h"
#include "Project_MOBA/Character/Minion/Controller/MyAIController.h"
#include "Project_MOBA/FunctionLibrary/MyBlueprintFunctionLibrary.h"
#include "Project_MOBA/GameModeBase/MyGameModeBase.h"
#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

AMinionBase::AMinionBase()
{
	SpawnLocation = CreateDefaultSubobject<USphereComponent>("Spawn Location");
}

void AMinionBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ThisClass::SpawnTimerCallBack, SpawnRate, true, DelayFirstSpawn);
}

void AMinionBase::SpawnTimerCallBack()
{
	
	SpawningMinion();
}

void AMinionBase::SpawningMinion()
{
	for (const auto& Struct : MinionToSpawn)
	{
		AActor* NewMinion = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), TSubclassOf<AActor>(Struct.MinionClass), SpawnLocation->GetComponentTransform(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn, this);
		AMinionCharacter* MinionCharacter = Cast<AMinionCharacter>(NewMinion);
		FGameplayTag OpponentMotherBaseTag = GetTeamTag().MatchesTagExact(MyGameplayTagsManager::Get().Team_White) ? MyGameplayTagsManager::Get().Team_Black : MyGameplayTagsManager::Get().Team_White;
		MinionCharacter->SetOpponentMotherBase(UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->GetTeamBaseMap().FindRef(OpponentMotherBaseTag));
		UGameplayStatics::FinishSpawningActor(MinionCharacter, SpawnLocation->GetComponentTransform());
	}
}