// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void GetFilteredActorListFromComponentList(const UObject* WorldContextObject, const FVector SpherePos,
														 float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass* InterfaceClassFilter,
														 const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors);
private:
};
