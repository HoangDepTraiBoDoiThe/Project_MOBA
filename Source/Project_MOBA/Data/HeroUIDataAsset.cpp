// Cu Nhat Hoang


#include "HeroUIDataAsset.h"

UHeroUIDataAsset::UHeroUIDataAsset()
{
}

FHeroUIDataStruct UHeroUIDataAsset::GetUIDataByHeroTag(FGameplayTag HeroTag)
{
	for (const auto& Struct : HeroUIData)
		if (Struct.HeroTag.MatchesTagExact(HeroTag)) return Struct;
	return FHeroUIDataStruct();
}
