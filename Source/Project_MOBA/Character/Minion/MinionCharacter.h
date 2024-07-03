// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "MinionCharacter.generated.h"

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

	// ICombatInterface override funcions.
	virtual void IncreaseXP2Give(const int32 XPAmount) override;
	virtual int32 GetXP() override;
	virtual int32 GetXPReward() override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	TObjectPtr<AMyAIController> MyAIController;

	int32 XP{1};
	UPROPERTY(EditDefaultsOnly)
	int32 XP2Give{1};
	
private:
	
};
