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

void UProjectileAbility::SpawnProjectile(const FVector& TargetLocation, FVector SpawnLoc, FVector ProjectileScale, bool bIgnorePitch)
{
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileToSpawn, FTransform(), GetAvatarActorFromActorInfo(), Cast<APawn>(GetAvatarActorFromActorInfo()));
	if (!Projectile)
	{
		UE_LOG(LogActor, Error, TEXT("Can not spawn projectile. Projectile is null"));
		return;
	}
	Projectile->SetOwner(GetAvatarActorFromActorInfo());

	SpawnLoc = SpawnLoc != FVector::Zero() ? SpawnLoc : GetAvatarActorFromActorInfo()->GetActorLocation();
	
	FVector Direction;
	if (bIgnorePitch) Direction = (TargetLocation - SpawnLoc).GetSafeNormal2D();
	else Direction = (TargetLocation - SpawnLoc).GetSafeNormal();
	//OrientateCharacter(Direction.Rotation());

	FTransform ProjectileTransform;
	ProjectileTransform.SetRotation(Direction.Rotation().Quaternion());
	ProjectileTransform.SetLocation(SpawnLoc);
	ProjectileTransform.SetScale3D(ProjectileScale);
	Projectile->SetSpecHandle(MakeGameplayEffect().Data);
	
	Projectile->FinishSpawning(ProjectileTransform);
}

void UProjectileAbility::SpawnProjectileAtSocketLocation(const FVector& TargetLocation, bool bIgnorePitch, FName SocketName, FVector ProjectileScale)
{
    if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	FVector SpawnLocation = Cast<ICombatInterface>(GetAvatarActorFromActorInfo())->GetWeaponSocketLocationByName(SocketName);
	SpawnProjectile(TargetLocation, SpawnLocation, ProjectileScale, bIgnorePitch);
}

void UProjectileAbility::SpawnProjectileAtSelectedLocation(const FVector& TargetLocation, FVector SpawnLoc, bool bIgnorePitch,
	FVector ProjectileScale)
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;
	SpawnProjectile(TargetLocation, SpawnLoc, ProjectileScale, bIgnorePitch);
}
