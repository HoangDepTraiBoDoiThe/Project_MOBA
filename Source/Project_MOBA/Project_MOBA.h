// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

// DEV MESSAGE | Priority | ErrorClass | Function | Message
#define CHECKF(Pointer, Priority, ErrorClassName, ErrorFunctionName,  Message) \
	checkf(Pointer, TEXT("DEV MESSAGE | %s | %s | %hs | %s "), *FString(Priority), *ErrorClassName, *ErrorFunctionName, *FString(Message));

