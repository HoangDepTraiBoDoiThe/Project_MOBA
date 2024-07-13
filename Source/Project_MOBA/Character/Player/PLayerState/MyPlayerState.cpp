// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerState.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
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
	DOREPLIFETIME(AMyPlayerState, PlayerLevel);
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;

}

void AMyPlayerState::RewardPlayer(const int32 XP2Increase)
{
	IncreaseXP(XP2Increase);
	const int32 TotalXP = XP + XP2Increase;
	const int32 LevelAtTotalXP = GetPlayerCharacter()->GetCharacterInfosDataAsset()->GetLevelAtXP(TotalXP, GetPlayerLevel());
	if (GetPlayerLevel() < 18 && GetPlayerLevel() < LevelAtTotalXP) GiveRewardToPlayer(TotalXP);
}

void AMyPlayerState::GiveRewardToPlayer(const int32 LevelAtTotalXP)
{
	const int32 CharacterNewLevel = GetPlayerCharacter()->GetCharacterInfosDataAsset()->GetLevelAtXP(LevelAtTotalXP);
	LevelUp(CharacterNewLevel);
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

void AMyPlayerState::LevelUp(const int32 NewLevel)
{
	const int32 OldValue = PlayerLevel;
	PlayerLevel = NewLevel;
	OnLeveling(OldValue);
	UGameplayStatics::SpawnEmitterAttached(GetPlayerCharacter()->GetLevelUpParticleSystem(), GetPlayerCharacter()->GetMesh());
}

void AMyPlayerState::IncreaseXP(int32 XPAmount)
{
	const int32 OldValue = XP;
	XP += XPAmount;
	OnXPChangeDelegate.Broadcast(XP, OldValue);
}

void AMyPlayerState::IncreaseXP2Give(const int32 XP2GiveAmount)
{
	XP2Give += XP2GiveAmount;
}

APlayerCharacter* AMyPlayerState::GetPlayerCharacter()
{
	if (!PlayerCharacter) PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	return PlayerCharacter;
}

void AMyPlayerState::RepNotify_XP(const int32 OldValue) const
{
	OnXPChangeDelegate.Broadcast(OldValue, XP);
}

void AMyPlayerState::RepNotify_PlayerLevel(const int32 OldValue)
{
	OnLeveling(OldValue);
}

void AMyPlayerState::OnLeveling(const int32 OldValue)
{
	if (AbilityPointDelegate.ExecuteIfBound(PlayerLevel))
	{
		UGameplayStatics::SpawnEmitterAttached(LevelUpParticle, GetPlayerCharacter()->GetMesh(), NAME_None, FVector(ForceInit), FRotator::ZeroRotator, FVector(1), EAttachLocation::SnapToTarget);
	}
	OnLevelChangeDelegate.Broadcast(PlayerLevel, OldValue);
}
