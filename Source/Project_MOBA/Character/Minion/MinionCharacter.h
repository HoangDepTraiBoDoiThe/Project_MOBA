// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Project_MOBA/Character/BaseCharacter.h"
#include "Project_MOBA/Interface/EnvironmentInterface.h"
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
class PROJECT_MOBA_API AMinionCharacter : public ABaseCharacter, public IEnvironmentInterface
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

	// IEnvironmentInterface functions
	virtual UMyAbilitySystemComponent* GetASC() override;
	virtual UBaseAttributeSet* GetAS() override;
	virtual UWidgetComponent* GetWidgetComponent() override;
	
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void PostInitializeComponents() override;
	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvironmentComponent> EnvironmentComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	TObjectPtr<AMyAIController> MyAIController;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	int32 XP{1};
	UPROPERTY(EditDefaultsOnly)
	int32 XP2Give{1};
	
private:
	
};
