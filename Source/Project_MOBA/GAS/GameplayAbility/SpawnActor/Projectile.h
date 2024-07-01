// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class ABaseCharacter;
class IAttackableInterface;
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
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const {return ProjectileMovementComponent;}

protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;
	void OneDestroyTimerCallback();

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	UPROPERTY(EditAnywhere)
	bool bShouldDestroyOnOver{true};

#pragma region Particle
	UPROPERTY(EditDefaultsOnly)
	float BulletParticleMultiply{1};
	// Extra main particle
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> BulletParticle;
	
	UPROPERTY(EditDefaultsOnly)
	bool bShouldRotateOpeningParticle{true};
	UPROPERTY(EditDefaultsOnly)
	float OpeningParticleMultiply{1};
	// Spawn particle, like postal.
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UParticleSystem>> OpeningParticles;
	
	UPROPERTY(EditDefaultsOnly)
	float HitParticleMultiply{1};
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> HitWorldParticle;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> HitCharacterParticle;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> NoHitParticle;
#pragma endregion 
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	TSharedPtr<FGameplayEffectSpec> EffectSpec;

	FTimerManager* TimerManager;
	FTimerHandle AutoDestroyTimerHande;
	
};
