// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UMyAssetManager& Get();
	virtual void StartInitialLoading() override;
	
};
