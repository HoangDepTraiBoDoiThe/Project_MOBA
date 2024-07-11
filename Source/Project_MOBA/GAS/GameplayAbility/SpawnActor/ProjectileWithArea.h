// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ProjectileWithArea.generated.h"

struct FActiveGameplayEffectHandle;
class UAbilitySystemComponent;
class UCapsuleComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AProjectileWithArea : public AProjectile
{
	GENERATED_BODY()

public:
	AProjectileWithArea();
	virtual void BeginPlay() override;

	UFUNCTION(Blueprintable)
	void SpawnArea();
	
protected:
	// Collision
	UFUNCTION()
	void OnAreaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                   int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                      int32 OtherBodyIndex);
	void OnEnding();
	void RemoveEffectAllTargetsOnArea();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> AreaCollision;
	
	TArray<UAbilitySystemComponent*> TargetsOnArea;

};
