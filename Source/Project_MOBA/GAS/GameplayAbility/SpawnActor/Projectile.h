// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UBoxComponent;
struct FGameplayEffectSpec;
class UProjectileMovementComponent;

UCLASS()
class PROJECT_MOBA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void SetSpecHandle(const TSharedPtr<FGameplayEffectSpec>& InSpec);

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	TSharedPtr<FGameplayEffectSpec> EffectSpec;

};
