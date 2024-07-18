// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "BaseCharacter.generated.h"

class UEnvironmentComponent;
class UWidgetComponent;
class UBoxComponent;
struct FCharacterAbilityStruct;
class UGameplayAbility;
class UCharacterInfosDataAsset;
class UAbilitySystemComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;

UCLASS()
class PROJECT_MOBA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable)
	UMyAbilitySystemComponent* GetMyAbilitySystemComponent() const;
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const { return BaseAttributeSet; }

	virtual void Die() override;
	UFUNCTION(BlueprintCallable)
	virtual void Death();
	UFUNCTION(BlueprintCallable)
	virtual FGameplayTag GetTeamTag() override;
	virtual FGameplayTag GetActorTag() override;
	
	// IGameplayTagAssetInterface override functions.
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	FORCEINLINE UCharacterInfosDataAsset* GetCharacterInfosDataAsset() const { return CharacterInfos; }
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetAnimMontageByTag(FGameplayTag Tag);
	TArray<FCharacterAbilityStruct> GetCharacterStartupAbilities();

	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetMeleCollisionBoundary() const {return MeleCollisionBoundary;}

	// ICombatInterface override functions.
	virtual UPrimitiveComponent* GetAttackableActor_Mesh() override;
	virtual FVector GetWeaponSocketLocationByName(FName SocketName) override;
	virtual AActor* GetOwningCombatActor() override {return this;}
	virtual void IncreaseXP2Give(const int32 XPAmount) override;
	virtual int32 GetXP() override;
	virtual int32 GetXPReward() override;

	UWidgetComponent* GetWidgetComponent() const;
	UFUNCTION(BlueprintCallable)
	void SetCurrentTargetActor(ABaseCharacter* Actor);

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ABaseCharacter> CurrentTargetActor;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag TeamTag;
	
	UPROPERTY()
	TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;
	UPROPERTY()
	UBaseAttributeSet* BaseAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category= "Character info|Character Specific")
	FGameplayTag CharacterTag;

	UPROPERTY(EditAnywhere, Category= "Character info")
	TObjectPtr<UCharacterInfosDataAsset> CharacterInfos;

	UPROPERTY(EditAnywhere)
	FName MeleSocketName{"MeleWeaponSocket"};
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> MeleCollisionBoundary;

	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UEnvironmentComponent> EnvironmentComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;
	int32 XP{1};
	UPROPERTY(EditDefaultsOnly)
	int32 XP2Give{1};
};
