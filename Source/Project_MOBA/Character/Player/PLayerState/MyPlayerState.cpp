// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Project_MOBA/Data/CharacterInfosDataAsset.h"
#include "Project_MOBA/GAS/ASC/MyAbilitySystemComponent.h"
#include "Project_MOBA/GAS/AttributeSet/BaseAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability System Component"));
	BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("Attribute Set"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	NetUpdateFrequency = 100;
}

void AMyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION(AMyPlayerState, XP, COND_InitialOrOwner);
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;

}

void AMyPlayerState::RewardPlayer(const int32 XP2Increase)
{
	const int32 TotalXP = XP + XP2Increase;
	FRewardForPlayerStruct RewardForPlayer;
	GetPlayerCharacter()->GetCharacterInfosDataAsset()->GetRewardForPlayersByXP(RewardForPlayer, TotalXP, GetPlayerLevel());
	GiveRewardToPlayer(RewardForPlayer, TotalXP);
}

void AMyPlayerState::GiveRewardToPlayer(const FRewardForPlayerStruct& Reward, const int32 TotalXP )
{
	LevelUp();
	SetXP(TotalXP);
	// TODO: Give Reward To Player.
}

void AMyPlayerState::SetXP(const int32 XP2Set)
{
	XP = XP2Set;
}

void AMyPlayerState::IncreaseXP2Give(const int32 XP2GiveAmount)
{
	XP += XP2GiveAmount;
}

void AMyPlayerState::LevelUp()
{
	PlayerLevel += 1;
}

void AMyPlayerState::SetCharacterLevel(const int32 Level)
{
	PlayerLevel = Level;
}

APlayerCharacter* AMyPlayerState::GetPlayerCharacter()
{
	if (!PlayerCharacter) PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	return PlayerCharacter;
}

void AMyPlayerState::RepNotify_XP(const int32 OldValue)
{
	
}
