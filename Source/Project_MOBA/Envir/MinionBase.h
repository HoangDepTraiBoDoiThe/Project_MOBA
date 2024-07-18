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

	// How many second between each Waves.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaveSpawnRate{20};

	// How many second between each minion spawn in a wave.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Rate;
	
	// How many normal waves before a Cannon wave
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float NumberNormalWavesBeforeBigWave{3};
	
	// Wait for how long in second before the first spawn.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DelayFirstSpawn;
	
	UPROPERTY(EditAnywhere)
	TArray<FMinionToSpawnStruct> MinionsToSpawn;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SpawnLocation;

	// Spawn functionality
	UFUNCTION(BlueprintCallable)
	TArray<TSubclassOf<AMinionCharacter>> GetNextWaveToResponse();
	UPROPERTY(BlueprintReadWrite)
	int32 NormalWaveRemainBeforeBigWave = NumberNormalWavesBeforeBigWave;
	UFUNCTION(BlueprintCallable)
	void SpawnAMinion(const TSubclassOf<AMinionCharacter> MinionClass);

	
private:
	
};
