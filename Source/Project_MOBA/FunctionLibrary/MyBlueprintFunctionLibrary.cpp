// Cu Nhat Hoang


#include "MyBlueprintFunctionLibrary.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Project_MOBA.h"

void UMyBlueprintFunctionLibrary::GetFilteredActorListFromComponentList(const UObject* WorldContextObject, const FVector SpherePos,
                                       float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass* InterfaceClassFilter,
                                       const TArray<AActor*>& ActorsToIgnore, TArray<AActor*>& OutActors)
{
	OutActors.Empty();

	TArray<UPrimitiveComponent*> OverlapComponents;
	bool bOverlapped = UKismetSystemLibrary::SphereOverlapComponents(WorldContextObject, SpherePos, SphereRadius, ObjectTypes, NULL, ActorsToIgnore, OverlapComponents);
	if (bOverlapped)
	{
		for (int32 i = 0; i < OverlapComponents.Num(); i++)
		{
			if (!OverlapComponents[i]) continue;

			CHECKF(InterfaceClassFilter, "High", "UMyBlueprintFunctionLibrary", __FUNCTION__, "InterfaceClassFilter is null")
			AActor* Owner = OverlapComponents[i]->GetOwner();
			if (InterfaceClassFilter && Owner->GetClass()->ImplementsInterface(InterfaceClassFilter))
			{
				OutActors.AddUnique(Owner);
			}
		}
	}
}
