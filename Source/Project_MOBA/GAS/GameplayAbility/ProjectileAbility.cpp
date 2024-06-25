// Cu Nhat Hoang

#include "ProjectileAbility.h"

#include "AbilitySystemComponent.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "SpawnActor/Projectile.h"

UProjectileAbility::UProjectileAbility()
{
}

FGameplayEffectSpecHandle UProjectileAbility::MakeGameplayEffect()
{
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(Effect, 1, ContextHandle);

	//SpecHandle.Data.Get()->SetSetByCallerMagnitude(MyGameplayTagsManager::Get().DamageType_Elemental_Fire, 10);
	return SpecHandle;
}

void UProjectileAbility::SpawnProjectile(const FVector& TargetLocation, FName SocketName, FVector ProjectileScale)
{
    if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileToSpawn, FTransform(), GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()));
	Projectile->SetOwner(GetAvatarActorFromActorInfo());

	const FVector Direction = (TargetLocation - GetAvatarActorFromActorInfo()->GetActorLocation()).GetSafeNormal2D();
	FVector SpawnLocation = Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeaponSocketLocationByName(SocketName);
	//OrientateCharacter(Direction.Rotation());
	
	FTransform ProjectileTransform;
	ProjectileTransform.SetRotation(Direction.Rotation().Quaternion());
	SpawnLocation = SpawnLocation != FVector::Zero() ? SpawnLocation : GetAvatarActorFromActorInfo()->GetActorLocation();
	ProjectileTransform.SetLocation(SpawnLocation);
	ProjectileTransform.SetScale3D(ProjectileScale);
	Projectile->SetActorScale3D(ProjectileScale);
	Projectile->SetSpecHandle(MakeGameplayEffect().Data);
	
	Projectile->FinishSpawning(ProjectileTransform);
}
