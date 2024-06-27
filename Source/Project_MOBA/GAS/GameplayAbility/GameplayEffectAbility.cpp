// Cu Nhat Hoang


#include "GameplayEffectAbility.h"

void UGameplayEffectAbility::OrientateCharacter(FRotator Rotator)
{
	GetAvatarActorFromActorInfo()->SetActorRotation(Rotator);
}
