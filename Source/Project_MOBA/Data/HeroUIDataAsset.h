// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "HeroUIDataAsset.generated.h"

class UImage;
struct FGameplayTag;
/**
 * 
 */
USTRUCT(Blueprintable, BlueprintType)
struct FAbilityUIStruct
{
	GENERATED_BODY()

	FAbilityUIStruct() {}
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture* AbilityIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterialInstance* AbilityBackGround = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag AbilityState = FGameplayTag();
	UPROPERTY(BlueprintReadOnly)
	int32 AbilityLevel = 1;
};

USTRUCT(Blueprintable, BlueprintType)
struct FHeroUIDataStruct
{
	GENERATED_BODY()

	FHeroUIDataStruct() {}
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HeroTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityUIStruct> AbilityUIData = TArray<FAbilityUIStruct>();
};

UCLASS()
class PROJECT_MOBA_API UHeroUIDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UHeroUIDataAsset();
	FHeroUIDataStruct GetUIDataByHeroTag(FGameplayTag HeroTag);

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FHeroUIDataStruct> HeroUIData;

};
