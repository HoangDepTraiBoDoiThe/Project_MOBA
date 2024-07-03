// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class AMinionCharacter;
class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MOBA_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();
	virtual void BeginPlay() override;
	AMinionCharacter* GetMinionCharacter();

	void SetupBehavior(UBehaviorTree* BehaviorTree);

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComponent() const {return BTComponent;}
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTreeComponent> BTComponent;

	UPROPERTY()
	TObjectPtr<AMinionCharacter> MinionCharacter;
private:
	
};
