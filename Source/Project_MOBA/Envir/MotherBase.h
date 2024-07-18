// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseEnvirActor.h"
#include "GameFramework/Actor.h"
#include "MotherBase.generated.h"

class UEnvironmentComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;
class USphereComponent;
class UBoxComponent;

UCLASS()
class PROJECT_MOBA_API AMotherBase : public ABaseEnvirActor
{
	GENERATED_BODY()
	
public:	
	AMotherBase();
	virtual void Tick(float DeltaTime) override;

	virtual void Die() override;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

};
