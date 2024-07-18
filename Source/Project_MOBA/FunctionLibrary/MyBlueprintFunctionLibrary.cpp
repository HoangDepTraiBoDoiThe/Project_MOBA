// Cu Nhat Hoang


#include "MyBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Project_MOBA/Project_MOBA.h"
#include "Project_MOBA/Character/Player/PlayerController/MyPlayerController.h"
#include "Project_MOBA/Character/Player/PLayerState/MyPlayerState.h"
#include "Project_MOBA/GameModeBase/MyGameModeBase.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/GameplayAbility/SpawnActor/Projectile.h"
#include "Project_MOBA/UI/MyHUD.h"
#include "Project_MOBA/UI/WidgetController/MainWidgetController.h"

void UMyBlueprintFunctionLibrary::GetFilteredCombatActorListFromOverlappedActors(const UObject* WorldContextObject, const FVector SpherePos,
                                                                        float SphereRadius, const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes, UClass* InterfaceClassFilter, FGameplayTag OwnerTeamTag,
                                                                        const TArray<AActor*>& ActorsToIgnore, TArray<ICombatInterface*>& OutActors)
{
	OutActors.Empty();

	TArray<UPrimitiveComponent*> OverlapComponents;
	const bool bOverlapped = UKismetSystemLibrary::SphereOverlapComponents(WorldContextObject, SpherePos, SphereRadius, ObjectTypes, NULL, ActorsToIgnore, OverlapComponents);
	if (bOverlapped)
	{
		for (int32 i = 0; i < OverlapComponents.Num(); i++)
		{
			if (!OverlapComponents[i]) continue;

			CHECKF(InterfaceClassFilter, "High", "UMyBlueprintFunctionLibrary", __FUNCTION__, "InterfaceClassFilter is null")
			ICombatInterface* OverlappedActors = Cast<ICombatInterface>(OverlapComponents[i]->GetOwner());
			if (InterfaceClassFilter && OverlappedActors && !OverlappedActors->GetTeamTag().MatchesTagExact(OwnerTeamTag))
			{
				OutActors.AddUnique(OverlappedActors);
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
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileToSpawn, FTransform(), Owner, Cast<APawn>(Instigator));
	if (!Projectile)
	{
		UE_LOG(LogActor, Error, TEXT("Can not spawn projectile. Projectile is null"));
		return nullptr;
	}
	SpawnLocation = !SpawnLocation.IsZero() ? SpawnLocation : (Owner != nullptr ? Owner->GetActorLocation() : FVector::Zero());

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

AProjectile* UMyBlueprintFunctionLibrary::SpawnHomingProjectile(const UObject* WorldContextObject,
	TSubclassOf<AProjectile> ProjectileToSpawn, const FGameplayEffectSpecHandle& EffectSpecHandle,
	FVector SpawnLocation, USceneComponent* HomingTargetComponent, FVector ProjectileScale, FGameplayTag AbilityTag,
	const float ActorInitialSpeed, AActor* Owner, APawn* Instigator)
{
	UWorld* World = WorldContextObject->GetWorld();
	AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileToSpawn, FTransform(), Owner, Cast<APawn>(Instigator));
	if (!Projectile)
	{
		UE_LOG(LogActor, Error, TEXT("Can not spawn projectile. Projectile is null"));
		return nullptr;
	}
	SpawnLocation = !SpawnLocation.IsZero() ? SpawnLocation : (Owner != nullptr ? Owner->GetActorLocation() : FVector::Zero());
	
	FTransform ProjectileTransform;
	ProjectileTransform.SetLocation(SpawnLocation);
	ProjectileTransform.SetScale3D(ProjectileScale);
	Projectile->SetSpecHandle(EffectSpecHandle);
	Projectile->SetAbilityTag(AbilityTag);
	
	if (Projectile->GetProjectileMovementComponent())
	{
		//Projectile->GetProjectileMovementComponent()->InitialSpeed = ActorInitialSpeed;
		Projectile->GetProjectileMovementComponent()->bIsHomingProjectile = true;
		Projectile->GetProjectileMovementComponent()->HomingTargetComponent = HomingTargetComponent;
		Projectile->GetProjectileMovementComponent()->HomingAccelerationMagnitude = ActorInitialSpeed;
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

FGameplayEffectSpecHandle UMyBlueprintFunctionLibrary::MakeEffectSpecHandleWithDamageTypeMap(TSubclassOf<UGameplayEffect> EffectClass, UAbilitySystemComponent* OwningASC, UGameplayAbility* OwningAbility,
	TMap<FGameplayTag, FMyEffectTypeStruct> EffectTypeMap)
{
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeMyGameplayEffectSpecHandle(OwningASC, EffectClass);
	for (const auto& Pair : EffectTypeMap)
	{
		const float BaseDamageAtAbilityLevel = Pair.Value.EffectValue.GetValueAtLevel(OwningAbility->GetAbilityLevel());
		EffectSpecHandle.Data->SetSetByCallerMagnitude(Pair.Key, BaseDamageAtAbilityLevel);
	}
	return EffectSpecHandle;
}

AMyGameModeBase* UMyBlueprintFunctionLibrary::GetMyGameModeBase(const UObject* WorldContextObject)
{
	const UWorld* WorldContext = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);
	if (WorldContext)
		return Cast<AMyGameModeBase>(WorldContext->GetAuthGameMode());

	return nullptr;
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
