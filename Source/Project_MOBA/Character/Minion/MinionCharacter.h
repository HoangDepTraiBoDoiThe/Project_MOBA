// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "MinionCharacter.generated.h"

class UWidgetComponent;
class UEnvironmentComponent;
class AMyAIController;
class UBehaviorTree;
class UBlackboardData;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMinionCharacter : public ABaseCharacter
{
	GENERATED_BODY()


public:
	AMinionCharacter();
	virtual void BeginPlay() override;
	virtual void Die() override;
	UBehaviorTree* GetMinionBehaviorTree() const {return BehaviorTree;}

	AMyAIController* GetMyAIController();
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvironmentComponent> EnvironmentComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	TObjectPtr<AMyAIController> MyAIController;
	
private:
	
};
