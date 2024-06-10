// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MultiplayerInstanceSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAfterOnCreateSessionComplete, bool, bWasSuccessful);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAfterOnSearchSessionComplete, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& SearchResult);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAfterOnJoinSessionComplete, FName SessionName, const EOnJoinSessionCompleteResult::Type Type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAfterOnDestroySessionComplete, bool, bWasSuccessful);

UCLASS()
class MULTIPLAYERPLUGIN_API UMultiplayerInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UMultiplayerInstanceSubsystem();

public:
	FAfterOnCreateSessionComplete AfterOnCreateSessionComplete;
	FAfterOnSearchSessionComplete AfterOnSearchSessionComplete;
	FAfterOnJoinSessionComplete AfterOnJoinSessionComplete;
	FAfterOnDestroySessionComplete AfterOnDestroySessionComplete;
	
	void CreateSession(int32 MaxPlayers = 4, FString TypeOfMatch = "FreeForAll");
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	void FindSession(FString MatchType, int32 MaxSessionResults);
	void OnSearchSessionComplete(bool bWasSuccessful);

	void JoinSession(const FOnlineSessionSearchResult& SearchResult);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type JoinSessionResult);

	void DestroySession();
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	
	
private:
	bool bOnlineSessionInterface_IsValid();
	
	int32 MaxPlayersLastCall = 0;
	FString TypeOfMatchLastCall;
	bool bCanCreateSessionOnDestroy {false};
	
	IOnlineSessionPtr OnlineSession;
	TSharedPtr<FOnlineSessionSearch> OnlineSearchSettings;
	
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	FDelegateHandle OnCreateSessionDelegateHandle;
	
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	FDelegateHandle OnFindSessionsDelegateHandle;

	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	FDelegateHandle OnJoinSessionsDelegateHandle;

	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FDelegateHandle OnDestroySessionsDelegateHandle;
	
};
