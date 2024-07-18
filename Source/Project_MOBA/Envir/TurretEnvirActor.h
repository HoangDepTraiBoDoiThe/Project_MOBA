// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseEnvirActor.h"
#include "TurretEnvirActor.generated.h"

class USphereComponent;
class AProjectile;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API ATurretEnvirActor : public ABaseEnvirActor
{
	GENERATED_BODY()

public:
	ATurretEnvirActor();
	virtual UPrimitiveComponent* GetAttackableActor_Mesh() override;

	UFUNCTION(BlueprintCallable)
	ABaseCharacter* GetTargetActor();

protected:
	virtual void BeginPlay() override;
	void AtackingTarget(AActor* ActorToAttack);
	UFUNCTION()
	void OnOpponentEnteringAttackingBoundary(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer AbilityTags;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> AttackingRangeComponent;
	UPROPERTY(EditAnywhere)
	float AttackingBoundary;
	
};
