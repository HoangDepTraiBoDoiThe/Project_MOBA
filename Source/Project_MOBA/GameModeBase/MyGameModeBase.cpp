// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "Kismet/KismetSystemLibrary.h"

void AMyGameModeBase::EndGame()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("Game Ended"), true, false, FLinearColor::Red);
}
