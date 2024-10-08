// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "Project_MOBA/Envir/MotherBase.h"
#include "MinionCharacter.generated.h"

class AMinionBase;
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
	AMotherBase* GetOpponentMotherBase() const {return OpponentMotherBase;}
	void SetOpponentMotherBase(AMotherBase* MotherBase) {OpponentMotherBase = MotherBase;}
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	TObjectPtr<AMyAIController> MyAIController;
	UPROPERTY()
	AMotherBase* OpponentMotherBase;
	
private:
	
};
