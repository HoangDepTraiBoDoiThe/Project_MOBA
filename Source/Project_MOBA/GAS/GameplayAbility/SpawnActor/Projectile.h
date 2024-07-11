// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class ABaseCharacter;
class UBoxComponent;
struct FGameplayEffectSpec;
class UProjectileMovementComponent;
UCLASS()

// Call SetupParticle after projectile spawned.
class PROJECT_MOBA_API AProjectile : public AActor
{
    GENERATED_BODY()
    
public: 
    AProjectile();

    virtual void Tick(float DeltaTime) override;
    
    void SetSpecHandle(const FGameplayEffectSpecHandle& InSpecHandle);
    FORCEINLINE void SetAbilityTag(const FGameplayTag& _AbilityTag) {AbilityTag = _AbilityTag;}
    
    FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
    UFUNCTION(BlueprintCallable)
    void SetupParticles(const FVector& SpawnLocation = FVector(0));

protected:
    virtual void BeginPlay() override;
    void SetupDestroyTimer();
    virtual void PostInitializeComponents() override;
    virtual void Destroyed() override;

    UFUNCTION(BlueprintCallable)
    void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,  int32 OtherBodyIndex);
    void OnDestroyTimerCallBack();

    // Components
    void RemoveEffectAllTargetsOnArea();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditAnywhere, Category = "Components")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(EditAnywhere, Category = "Components")
    TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

    FGameplayTag AbilityTag;
    TArray<UAbilitySystemComponent*> TargetsOnArea;

    // Behavior
    UPROPERTY(EditAnywhere, Category = "Behavior")
    bool bShouldDestroyOnOver{true};

    // Particles
    TObjectPtr<UParticleSystemComponent> MainParticleSystemComponent;
    UPROPERTY(EditDefaultsOnly, Category = "Particles|Bullet")
    float BulletParticleMultiply{1.0f};

    UPROPERTY(EditDefaultsOnly, Category = "Particles|Bullet")
    TObjectPtr<UParticleSystem> BulletParticle;
    
    UPROPERTY(EditDefaultsOnly, Category = "Particles|Opening")
    bool bShouldRotateOpeningParticle{true};

    UPROPERTY(EditDefaultsOnly, Category = "Particles|Opening")
    float OpeningParticleMultiply{1.0f};

    UPROPERTY(EditDefaultsOnly, Category = "Particles|Opening")
    TArray<TObjectPtr<UParticleSystem>> OpeningParticles;
    
    UPROPERTY(EditDefaultsOnly, Category = "Particles|Hit")
    float HitParticleMultiply{1.0f};

    UPROPERTY(EditDefaultsOnly, Category = "Particles|Hit")
    TObjectPtr<UParticleSystem> HitWorldParticle;

    UPROPERTY(EditDefaultsOnly, Category = "Particles|Hit")
    TObjectPtr<UParticleSystem> HitCharacterParticle;

    UPROPERTY(EditDefaultsOnly, Category = "Particles|Hit")
    TObjectPtr<UParticleSystem> NoHitParticle;

    FGameplayEffectSpecHandle EffectSpecHandle;
    
private:

    FTimerManager* TimerManager;
    FTimerHandle AutoDestroyTimerHandle;
};
