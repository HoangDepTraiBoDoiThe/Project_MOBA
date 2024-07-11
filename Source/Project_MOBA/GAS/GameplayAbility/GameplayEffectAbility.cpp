// Cu Nhat Hoang


#include "GameplayEffectAbility.h"

void UGameplayEffectAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UGameplayEffectAbility::OrientateCharacter(FRotator Rotator)
{
	GetAvatarActorFromActorInfo()->SetActorRotation(Rotator);
}
