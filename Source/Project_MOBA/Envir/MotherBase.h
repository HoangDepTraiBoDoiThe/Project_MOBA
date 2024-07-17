// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Actor.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "MotherBase.generated.h"

class USphereComponent;
class UBoxComponent;

UCLASS()
class PROJECT_MOBA_API AMotherBase : public AActor, public ICombatInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	AMotherBase();
	virtual void Tick(float DeltaTime) override;

	// IGameplayTagAssetInterface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	
	// ICombatInterface
	virtual AActor* GetOwningCombatActor() override {return this;}
	virtual UPrimitiveComponent* GetAttackableActor_Mesh() override;
	virtual void Die() override;
	virtual FGameplayTag GetTeamTag() override {return TeamTag;}
	virtual FGameplayTag GetActorTag() override {return ActorTag;}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag TeamTag;	

	UPROPERTY(EditAnywhere)
	FGameplayTag ActorTag;	
};
