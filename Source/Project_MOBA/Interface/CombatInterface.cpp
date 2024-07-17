// Cu Nhat Hoang


#include "CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

FVector ICombatInterface::GetWeaponSocketLocationByName(FName SocketName)
{
	if (!GetAttackableActor_Mesh()) return FVector();
	return GetAttackableActor_Mesh()->GetSocketLocation(SocketName);
}

int32 ICombatInterface::GetXP()
{
	return 0;
}

int32 ICombatInterface::GetXPReward()
{
	return 0;

}

void ICombatInterface::IncreaseXP2Give(const int32 XPAmount)
{
}
