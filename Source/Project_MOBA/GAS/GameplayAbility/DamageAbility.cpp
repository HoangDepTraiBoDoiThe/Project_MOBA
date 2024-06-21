// Cu Nhat Hoang


#include "DamageAbility.h"

void UDamageAbility::OrientateCharacter(FRotator Rotator)
{
	GetAvatarActorFromActorInfo()->SetActorRotation(Rotator);
}
