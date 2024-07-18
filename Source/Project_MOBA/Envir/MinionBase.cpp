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

}

void AMinionBase::SpawnAMinion(const TSubclassOf<AMinionCharacter> MinionClass)
{
	if (!MinionClass) return;
	AActor* NewMinion = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), TSubclassOf<AActor>(MinionClass), SpawnLocation->GetComponentTransform(), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn, this);
	AMinionCharacter* MinionCharacter = Cast<AMinionCharacter>(NewMinion);
	const FGameplayTag OpponentMotherBaseTag = GetTeamTag().MatchesTagExact(MyGameplayTagsManager::Get().Team_White) ? MyGameplayTagsManager::Get().Team_Black : MyGameplayTagsManager::Get().Team_White;
	MinionCharacter->SetOpponentMotherBase(UMyBlueprintFunctionLibrary::GetMyGameModeBase(GetWorld())->GetTeamBaseMap().FindRef(OpponentMotherBaseTag));
	UGameplayStatics::FinishSpawningActor(MinionCharacter, SpawnLocation->GetComponentTransform());
}

TArray<TSubclassOf<AMinionCharacter>> AMinionBase::GetNextWaveToResponse()
{
	TArray<TSubclassOf<AMinionCharacter>> NextWaveToResponse;
	bool bIsSuperWave = false;

	if (NormalWaveRemainBeforeBigWave <= 0)
	{
		bIsSuperWave = true;
		NormalWaveRemainBeforeBigWave = NumberNormalWavesBeforeBigWave;
	}

	for (const auto& Struct : MinionsToSpawn)
	{
		const bool bIsSuperMinionStruct = Struct.MinionTag.MatchesTag(FGameplayTag::RequestGameplayTag("Character.Minion.Super"));
        
		if (bIsSuperMinionStruct == bIsSuperWave)
		{
			for (int32 i = 0; i < Struct.SpawnCount; i++)
			{
				NextWaveToResponse.Add(Struct.MinionClass);
			}
		}
	}

	if (!bIsSuperWave)
	{
		NormalWaveRemainBeforeBigWave--;
	}
    
	return NextWaveToResponse;
}