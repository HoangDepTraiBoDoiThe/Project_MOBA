// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;
struct FCharacterAbilityStruct;
class UGameplayAbility;
class UCharacterInfosDataAsset;
class UAbilitySystemComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;

UCLASS()
class PROJECT_MOBA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
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

	// ICombatInterface override funcions.
	virtual USkeletalMeshComponent* GetAttackableActorMesh() override;
	virtual FVector GetWeaponSocketLocationByName(FName SocketName) override;
	virtual void Die() override;
	UFUNCTION(BlueprintCallable)
	virtual void Death();
	virtual int32 GetXP() override {return 0;}
	virtual int32 GetXPReward() override {return 0;}
	virtual void IncreaseXP2Give(const int32 XPAmount) override {}
	UFUNCTION(BlueprintCallable)
	virtual FGameplayTag GetTeamTag() override;
	virtual FGameplayTag GetCharacterTag() override;

	FORCEINLINE UCharacterInfosDataAsset* GetCharacterInfosDataAsset() const { return CharacterInfos; }
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetAnimMontageByTag(FGameplayTag Tag);
	TArray<FCharacterAbilityStruct> GetCharacterStartupAbilities();

	UFUNCTION(BlueprintCallable)
	UBoxComponent* GetMeleCollisionBoundary() const {return MeleCollisionBoundary;}


protected:
	virtual void BeginPlay() override;

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
};
