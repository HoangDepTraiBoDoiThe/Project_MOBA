// Cu Nhat Hoang


#include "MyAssetManager.h"

#include "Project_MOBA/Managers/GameplayTagManager/MyGameplayTagsManager.h"

UMyAssetManager& UMyAssetManager::Get()
{
	return *Cast<UMyAssetManager>(GEngine->AssetManager.Get());
}

void UMyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	MyGameplayTagsManager::Get().InitNativeGameplayTags();
}
