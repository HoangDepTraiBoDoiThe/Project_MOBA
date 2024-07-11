// Cu Nhat Hoang


#include "MyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Project_MOBA.h"
#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/GameplayAbility/SpawnActor/Projectile.h"
#include "Project_MOBA/UI/MyHUD.h"
#include "Project_MOBA/UI/WidgetController/BaseWidgetController.h"

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

AProjectile* UMyBlueprintFunctionLibrary::SpawnProjectile(const UObject* WorldContextObject,
                                                          const TSubclassOf<AProjectile> ProjectileToSpawn,
                                                          const FGameplayEffectSpecHandle& EffectSpecHandle,
                                                          FVector SpawnLocation,
                                                          const FVector& TargetLocation, const FVector ProjectileScale, FGameplayTag AbilityTag, AActor* Owner, APawn* Instigator,
                                                          const bool bMoving, const float ActorInitialSpeed)
{
	UWorld* World = WorldContextObject->GetWorld();
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileToSpawn, FTransform(), Owner,

	Cast<APawn>(Instigator));
	if (!Projectile)
	{
		UE_LOG(LogActor, Error, TEXT("Can not spawn projectile. Projectile is null"));
		return nullptr;
	}
	SpawnLocation = !SpawnLocation.IsZero()
		                ? SpawnLocation
		                : (Owner != nullptr ? Owner->GetActorLocation() : FVector::Zero());

	const FVector Direction = (TargetLocation - SpawnLocation).GetSafeNormal();
	//OrientateCharacter(Direction.Rotation());

	FTransform ProjectileTransform;
	ProjectileTransform.SetRotation(Direction.Rotation().Quaternion());
	ProjectileTransform.SetLocation(SpawnLocation);
	ProjectileTransform.SetScale3D(ProjectileScale);
	Projectile->SetSpecHandle(EffectSpecHandle);
	Projectile->SetAbilityTag(AbilityTag);

	if (Projectile->GetProjectileMovementComponent())
	{
		Projectile->GetProjectileMovementComponent()->InitialSpeed = bMoving ? ActorInitialSpeed : 0.f;
	}

	Projectile->FinishSpawning(ProjectileTransform);
	return Projectile;
}

FGameplayEffectSpecHandle UMyBlueprintFunctionLibrary::MakeMyGameplayEffectSpecHandle(const UAbilitySystemComponent* ASC,
                                                                                      const TSubclassOf<UGameplayEffect> EffectClass, const int32 EffectLevel)
{
	const FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(EffectClass, EffectLevel, ContextHandle);

	//SpecHandle.Data.Get()->SetSetByCallerMagnitude(MyGameplayTagsManager::Get().DamageType_Elemental_Fire, 10);
	return SpecHandle;
}

UMainWidgetController* UMyBlueprintFunctionLibrary::GetMainWidgetController(const UObject* WorldContextObject)
{
	const FWidgetControllerStruct* WidgetControllerInfos = MakeWidgetControllerInfos(WorldContextObject);
	AMyHUD* MyHUD = Cast<AMyHUD>(WidgetControllerInfos->PC->GetHUD());
	return MyHUD->GetMainWidgetController(*WidgetControllerInfos);
}

FWidgetControllerStruct* UMyBlueprintFunctionLibrary::MakeWidgetControllerInfos(const UObject* WorldContextObject)
{
	const UWorld* WorldContext = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	AMyPlayerController* PC = Cast<AMyPlayerController>( WorldContext->GetFirstLocalPlayerFromController()->GetPlayerController(WorldContext));
	AMyPlayerState* PS = PC->GetMyPlayerState();
	UMyAbilitySystemComponent* ASC = PC->GetPlayerCharacter()->GetMyAbilitySystemComponent();
	UBaseAttributeSet* AS = PS->GetBaseAttributeSet();
	
	return new FWidgetControllerStruct(PC, PS, ASC, AS);
}
