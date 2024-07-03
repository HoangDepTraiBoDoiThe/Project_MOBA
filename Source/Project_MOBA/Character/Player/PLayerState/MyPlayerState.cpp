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
	SetXP(TotalXP);
	const int32 LevelAtTotalXP = GetPlayerCharacter()->GetCharacterInfosDataAsset()->GetLevelAtXP(TotalXP, GetPlayerLevel());
	if (GetPlayerLevel() < LevelAtTotalXP) GiveRewardToPlayer();
}

void AMyPlayerState::GiveRewardToPlayer()
{
	LevelUp();
	UCurveTable* RewardTable = GetPlayerCharacter()->GetRewardTable();
	TMap<FName, FGameplayTag> RewardAttributeMap = GetPlayerCharacter()->GetRewardAttributeMap();
	if (RewardTable)
	{
		TSubclassOf<UGameplayEffect> RewardGE = GetPlayerCharacter()->GetRewardGE();
		const FGameplayEffectSpecHandle RewardHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(RewardGE, 1, GetAbilitySystemComponent()->MakeEffectContext());
		const TMap<FName, FSimpleCurve*> RewardRowMap = RewardTable->GetSimpleCurveRowMap();
		for (const auto& Pair : RewardAttributeMap)
		{
			const FSimpleCurve* AttributeRow = RewardRowMap.FindRef(Pair.Key);
			const int32 AttributeRewardPoints = AttributeRow->Eval(GetPlayerLevel());
			RewardHandle.Data->SetSetByCallerMagnitude(Pair.Value, AttributeRewardPoints);
		}
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*RewardHandle.Data);
	}
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
