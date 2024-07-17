// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseEnvirActor.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "MinionBase.generated.h"

class USphereComponent;
class AMinionCharacter;

USTRUCT(Blueprintable, BlueprintType)
struct FMinionToSpawnStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag MinionTag = FGameplayTag();
	UPROPERTY(EditAnywhere)
	TSubclassOf<AMinionCharacter> MinionClass = nullptr;
	UPROPERTY(EditAnywhere)
	int32 SpawnCount = 0;
};

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMinionBase : public ABaseEnvirActor
{
	GENERATED_BODY()

public:
	AMinionBase();
	
protected:
	virtual void BeginPlay() override;
	void SpawningMinion();
	void SpawnTimerCallBack();

	// How many second between each spawn.
	UPROPERTY(EditAnywhere)
	float SpawnRate;
	// Wait for how long in second before the first spawn.
	UPROPERTY(EditAnywhere)
	float DelayFirstSpawn;
	UPROPERTY(EditAnywhere)
	TArray<FMinionToSpawnStruct> MinionToSpawn;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SpawnLocation;

	FTimerHandle SpawnTimer;
};
