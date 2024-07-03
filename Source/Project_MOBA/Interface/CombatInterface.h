// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
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
	virtual FVector GetWeaponSocketLocationByName(FName SocketName = "PuzzleSocket") = 0;
	virtual USkeletalMeshComponent* GetAttackableActorMesh() = 0;
	virtual int32 GetXP() = 0;
	virtual int32 GetXPReward() = 0;
	virtual void IncreaseXP2Give(const int32 XPAmount) = 0;
	virtual void Die() = 0;	
};
