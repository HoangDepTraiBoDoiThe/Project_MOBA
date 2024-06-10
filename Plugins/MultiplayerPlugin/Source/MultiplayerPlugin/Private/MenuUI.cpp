// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuUI.h"
#include "MultiplayerInstanceSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Components/Button.h"
#include "Engine/GameEngine.h"

void UMenuUI::SetupMenu(FString typeOfMatch_Create, FString typeOfMatch_Search, int32 maxSessionSearch, FString path2Session)
{
	
	TypeOfMatch_Create = typeOfMatch_Create;
	TypeOfMatch_Search = typeOfMatch_Search;
	MaxSessionSearch = maxSessionSearch;

	Path2Session = FString::Printf(TEXT("%s?listen"), *path2Session);

	APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
	
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;	
	
	if (PlayerController)
	{
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(InputMode);
	}
	
	MultiplayerInstanceSubsystem = GetGameInstance()->GetSubsystem<UMultiplayerInstanceSubsystem>();

	if (MultiplayerInstanceSubsystem)
	{
		MultiplayerInstanceSubsystem->AfterOnCreateSessionComplete.AddDynamic(this, &UMenuUI::OnCreateSessionComplete);
		MultiplayerInstanceSubsystem->AfterOnSearchSessionComplete.AddUObject(this, &UMenuUI::OnSearchSessionComplete);
		MultiplayerInstanceSubsystem->AfterOnJoinSessionComplete.AddUObject(this, &UMenuUI::OnJoinSessionComplete);
		MultiplayerInstanceSubsystem->AfterOnDestroySessionComplete.AddDynamic(this, &UMenuUI::OnDestroySessionComplete);
	}
}

void UMenuUI::NativeDestruct()
{
	Super::NativeDestruct();

	
	if (APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController())
	{
		const FInputModeGameOnly InputMode;
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(InputMode);
	}
}

bool UMenuUI::Initialize()
{
	if (!Super::Initialize()) return false;
	
	if (HostGame)
		HostGame->OnClicked.AddDynamic(this, &ThisClass::Host);
	if (JoinGame)
		JoinGame->OnClicked.AddDynamic(this, &ThisClass::Join);
	
	return true;
}

void UMenuUI::Host()
{
	MultiplayerInstanceSubsystem->CreateSession(100, TypeOfMatch_Create);
}

void UMenuUI::Join()
{
	MultiplayerInstanceSubsystem->FindSession(TypeOfMatch_Search, MaxSessionSearch);
}

void UMenuUI::OnCreateSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, FString::Printf(TEXT("Session Created")));
		GetWorld()->ServerTravel(Path2Session);
	}
}

void UMenuUI::OnSearchSessionComplete(bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	if (bWasSuccessful && SearchResults.Num() != 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("Found a Session")));

		for (const FOnlineSessionSearchResult& result : SearchResults)
		{
			FString MatchType;
			result.Session.SessionSettings.Get(FName("MatchType"), MatchType);
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(
			TEXT("All conditions validated - Search result: (%hhd, Number of sessions: %d, MatchType: %s)"), bWasSuccessful, SearchResults.Num(), *MatchType));
			if (MatchType == TypeOfMatch_Search)
			{
				MultiplayerInstanceSubsystem->JoinSession(result);
				GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("Calling JoinSession() - Start")));
				return;
			}
			GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(
			TEXT("Unable to join session - Step 2. All Match Type (Server) is not the same as Match Type (Client)")));
		}
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(
			TEXT("Not all conditions validated - Unable to Join session - Step 2: Search result (%hhd, Number of sessions: %d)"), bWasSuccessful, SearchResults.Num()));
}

void UMenuUI::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Type)
{
	FString type = FString::FromInt(static_cast<int32>(Type));
	
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(
		TEXT("JoinSession - LastCallBack. Condition: %s, SessionName: %s"), *type, *SessionName.ToString()));
	
	
	if (Type == EOnJoinSessionCompleteResult::Success)
	{

		const IOnlineSessionPtr OnlineSession = IOnlineSubsystem::Get()->GetSessionInterface();

		FString address;
		OnlineSession->GetResolvedConnectString(SessionName, address);
		
		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		PlayerController->ClientTravel(address, ETravelType::TRAVEL_Absolute);
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Cyan, FString::Printf(TEXT("Joined a session - Complete - Start traveling . . .")));

	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(
			TEXT("Unable to join session - Last Step. Condition: %s, SessionName: %s"), *type, *SessionName.ToString()));
}

void UMenuUI::OnDestroySessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("The previous session has been destroyed")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Can't destroy the exiting session")));
}

