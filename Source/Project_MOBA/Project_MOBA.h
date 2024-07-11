// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// DEV MESSAGE | Priority | ErrorClass | Function | Message
#define CHECKF(Pointer, Priority, ErrorClassName, ErrorFunctionName,  Message) \
	checkf(Pointer, TEXT("DEV MESSAGE | %s | %s | %hs | %s "), *FString(Priority), *ErrorClassName, *ErrorFunctionName, *FString(Message));

//		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Try activate ability %s is %s"), *InputTag.GetTagName().ToString(), bSuccessfull ? *FString("Successfully") : *FString("Failed")));

#define EOTQ_GroundObject EObjectTypeQuery::ObjectTypeQuery7
#define EOTQ_TurretObject EObjectTypeQuery::ObjectTypeQuery8
#define EOTQ_CharacterObject EObjectTypeQuery::ObjectTypeQuery9
#define EOTQ_ProjectileObject EObjectTypeQuery::ObjectTypeQuery10
#define EOTQ_PawnObject EObjectTypeQuery::ObjectTypeQuery3

#define ECC_Turret ECollisionChannel::ECC_GameTraceChannel1
#define ECC_Ground ECollisionChannel::ECC_GameTraceChannel2
#define ECC_Character ECollisionChannel::ECC_GameTraceChannel3
#define ECC_Projectile ECollisionChannel::ECC_GameTraceChannel4