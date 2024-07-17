// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_MOBA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual FVector GetWeaponSocketLocationByName(FName SocketName = "MuzzleSocket");
	virtual AActor* GetOwningCombatActor() = 0;
	virtual int32 GetXP();
	virtual int32 GetXPReward();
	virtual void IncreaseXP2Give(const int32 XPAmount);
	virtual void Die() = 0;
	virtual FGameplayTag GetTeamTag() = 0;
	virtual FGameplayTag GetActorTag() = 0;
	
	// For highlighting
	virtual UPrimitiveComponent* GetAttackableActor_Mesh() = 0;
};
