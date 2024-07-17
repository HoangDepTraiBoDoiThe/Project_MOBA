// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Actor.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "Project_MOBA/Interface/EnvironmentInterface.h"
#include "MotherBase.generated.h"

class UEnvironmentComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;
class USphereComponent;
class UBoxComponent;

UCLASS()
class PROJECT_MOBA_API AMotherBase : public AActor, public ICombatInterface, public IGameplayTagAssetInterface, public IAbilitySystemInterface, public IEnvironmentInterface
{
	GENERATED_BODY()
	
public:	
	AMotherBase();
	virtual void Tick(float DeltaTime) override;

	// IEnvironmentInterface
	virtual UMyAbilitySystemComponent* GetASC() override;
	virtual UBaseAttributeSet* GetAS() override;
	virtual UWidgetComponent* GetWidgetComponent() override;
	
	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return Cast<UAbilitySystemComponent>(MyAbilitySystemComponent);}
	UMyAbilitySystemComponent* GetMyAbilitySystemComponent() const {return MyAbilitySystemComponent;}
	UBaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}
	
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

	TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;
	TObjectPtr<UBaseAttributeSet> BaseAttributeSet;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvironmentComponent> EnvironmentComponent;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> DefaultAttributeValues;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag TeamTag;	

	UPROPERTY(EditAnywhere)
	FGameplayTag ActorTag;	
};
