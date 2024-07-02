// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Project_MOBA/Interface/AttackableInterface.h"
#include "Project_MOBA/Interface/CombatInterface.h"
#include "BaseCharacter.generated.h"

class UGameplayAbility;
class UCharacterInfosDataAsset;
class UAbilitySystemComponent;
class UBaseAttributeSet;
class UMyAbilitySystemComponent;

UCLASS()
class PROJECT_MOBA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IAttackableInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UMyAbilitySystemComponent* GetMyAbilitySystemComponent() const;
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const {return BaseAttributeSet;}

	virtual USkeletalMeshComponent* GetAttackableActorMesh() override;
	virtual FVector GetWeaponSocketLocationByName(FName SocketName) override;	

	FORCEINLINE FGameplayTag GetCharacterTag() const {return CharacterTag;}
	FORCEINLINE UCharacterInfosDataAsset* GetCharacterInfosDataAsset() const {return CharacterInfos;}
	TArray<TSubclassOf<UGameplayAbility>>* GetCharacterStartupAbilities() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;
	UPROPERTY()
	UBaseAttributeSet* BaseAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category= "Hero info")
	FGameplayTag CharacterTag;
	
	UPROPERTY(EditAnywhere, Category= "Character info")
	TObjectPtr<UCharacterInfosDataAsset> CharacterInfos;
};
