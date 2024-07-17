// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "MotherBase.generated.h"

class UEnvironmentComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;
class USphereComponent;
class UBoxComponent;

UCLASS()
class PROJECT_MOBA_API AMotherBase : public ABaseCharacter
{
	GENERATED_BODY()
	
public:	
	AMotherBase();
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void Die() override;

protected:
	virtual void BeginPlay() override;

};
