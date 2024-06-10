// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerInstanceSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"

UMultiplayerInstanceSubsystem::UMultiplayerInstanceSubsystem():
OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete)),
OnFindSessionsCompleteDelegate(FOnFindSessionsCompleteDelegate::CreateUObject(this, &ThisClass::OnSearchSessionComplete)),
OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnJoinSessionComplete)),
OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &ThisClass::OnDestroySessionComplete))
{
}

void UMultiplayerInstanceSubsystem::CreateSession(int32 MaxPlayers, FString TypeOfMatch)
{
	if (!bOnlineSessionInterface_IsValid()) return;
	
	OnCreateSessionDelegateHandle = OnlineSession->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

	const FNamedOnlineSession* ExitingSession = OnlineSession->GetNamedSession(NAME_GameSession);
	if (ExitingSession != nullptr)
	{
		bCanCreateSessionOnDestroy = true;
		MaxPlayersLastCall = MaxPlayers;
		TypeOfMatchLastCall = TypeOfMatch;
		DestroySession();
	}
	
	const TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings);
	
	SessionSettings->bShouldAdvertise = true;	
	SessionSettings->bUsesPresence = true;	
	SessionSettings->bAllowJoinInProgress = true;	
	SessionSettings->bAllowJoinViaPresence = true;	
	SessionSettings->bUseLobbiesIfAvailable = true;
	SessionSettings->bIsLANMatch = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	SessionSettings->BuildUniqueId = 1;
	SessionSettings->NumPublicConnections = MaxPlayers;
	SessionSettings->Set(FName("MatchType"), TypeOfMatch, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!OnlineSession->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *SessionSettings))
	{
		OnlineSession->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionDelegateHandle);
		AfterOnCreateSessionComplete.Broadcast(false);
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Unable to create session")));
	}
}

void UMultiplayerInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (!bOnlineSessionInterface_IsValid())
	{
		AfterOnCreateSessionComplete.Broadcast(false);
		return;
	}

	FString OnlineSubsysName = IOnlineSubsystem::Get()->GetSubsystemName().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("OnlineSubsysName: %s"), *OnlineSubsysName));
	
	OnlineSession->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionDelegateHandle);
	AfterOnCreateSessionComplete.Broadcast(bWasSuccessful);
}

void UMultiplayerInstanceSubsystem::FindSession(FString MatchType, int32 MaxSessionResults)
{
	if (!bOnlineSessionInterface_IsValid())
	{
		return;
	}

	OnFindSessionsDelegateHandle = OnlineSession->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);
	
	OnlineSearchSettings = MakeShareable(new FOnlineSessionSearch);
	OnlineSearchSettings->MaxSearchResults = MaxSessionResults;
	OnlineSearchSettings->bIsLanQuery = IOnlineSubsystem::Get()->GetSubsystemName() == "NULL" ? true : false;
	OnlineSearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("Calling FindSession() - Start")));
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!OnlineSession->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), OnlineSearchSettings.ToSharedRef()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Unable to join(find) session - Step 1")));
		OnlineSession->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsDelegateHandle);
		AfterOnSearchSessionComplete.Broadcast(false, TArray<FOnlineSessionSearchResult>());
	}
}

void UMultiplayerInstanceSubsystem::OnSearchSessionComplete(bool bWasSuccessful)
{
	if (!bOnlineSessionInterface_IsValid())
	{
		AfterOnSearchSessionComplete.Broadcast(false, TArray<FOnlineSessionSearchResult>());
		return;
	}
	FString OnlineSubsysName = IOnlineSubsystem::Get()->GetSubsystemName().ToString();
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("OnlineSubsysName: %s"), *OnlineSubsysName));

	OnlineSession->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsDelegateHandle);
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("Called FindSession() condition: %hhd"), bWasSuccessful));
	AfterOnSearchSessionComplete.Broadcast(bWasSuccessful, OnlineSearchSettings->SearchResults);
}

void UMultiplayerInstanceSubsystem::JoinSession(const FOnlineSessionSearchResult& SearchResult)
{
	if (!bOnlineSessionInterface_IsValid())
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("Joining a session - Step 1")));

	OnJoinSessionsDelegateHandle = OnlineSession->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if (!OnlineSession->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SearchResult))
	{
		OnlineSession->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionsDelegateHandle);
		GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("Unable to join session - Step 3")));
		AfterOnJoinSessionComplete.Broadcast(NAME_GameSession, EOnJoinSessionCompleteResult::UnknownError);
	}
}

void UMultiplayerInstanceSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinSessionResult)
{
	if (!bOnlineSessionInterface_IsValid())
	{
		AfterOnJoinSessionComplete.Broadcast(NAME_GameSession, EOnJoinSessionCompleteResult::UnknownError);
		return;
	}

	FString joinSessionResult = FString::FromInt(static_cast<int32>(JoinSessionResult));
	OnlineSession->ClearOnJoinSessionCompleteDelegate_Handle(OnJoinSessionsDelegateHandle);
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Blue, FString::Printf(TEXT("Joining a session - Step 2. Condition: %s"), *joinSessionResult));
	AfterOnJoinSessionComplete.Broadcast(NAME_GameSession, JoinSessionResult);
}

void UMultiplayerInstanceSubsystem::DestroySession()
{
	if (!bOnlineSessionInterface_IsValid())
	{
		AfterOnDestroySessionComplete.Broadcast(false);
		return;
	}

	OnDestroySessionsDelegateHandle = OnlineSession->AddOnDestroySessionCompleteDelegate_Handle(OnDestroySessionCompleteDelegate);
	if (!OnlineSession->DestroySession(NAME_GameSession))
	{
		OnlineSession->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionsDelegateHandle);
		AfterOnDestroySessionComplete.Broadcast(false);
	}
}

void UMultiplayerInstanceSubsystem::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	AfterOnDestroySessionComplete.Broadcast(bWasSuccessful);
	OnlineSession->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroySessionsDelegateHandle);
	if (bWasSuccessful && bCanCreateSessionOnDestroy)
	{
		bCanCreateSessionOnDestroy = false;
		CreateSession(MaxPlayersLastCall, TypeOfMatchLastCall);
	}
}

bool UMultiplayerInstanceSubsystem::bOnlineSessionInterface_IsValid()
{
	if (!OnlineSession.IsValid())
	{
		if (IOnlineSubsystem::Get())
		{
			OnlineSession = IOnlineSubsystem::Get()->GetSessionInterface();
		}
	}

	return OnlineSession.IsValid();
}


