// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuUI.generated.h"

namespace EOnJoinSessionCompleteResult
{
	enum Type : int;
}

class UButton;
class UMultiplayerInstanceSubsystem;
/**
 * 
 */
UCLASS()
class MULTIPLAYERPLUGIN_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetupMenu(FString typeOfMatch_Create = "FreeForAll", FString typeOfMatch_Search = "FreeForAll", int32 maxSessionSearch = 10000, FString path2Session = "/Game/ThirdPerson/Maps/Lobby");
	virtual void NativeDestruct() override;

protected:
	virtual bool Initialize() override;
	
private:
	UPROPERTY()
	UMultiplayerInstanceSubsystem* MultiplayerInstanceSubsystem;
	
	UPROPERTY(meta=(BindWidget))
	UButton* HostGame;

	UPROPERTY(meta=(BindWidget))
	UButton* JoinGame;

	FString TypeOfMatch_Create;
	FString TypeOfMatch_Search;
	int32 MaxSessionSearch;
	FString Path2Session;

	UFUNCTION()
	void Host();
	
	UFUNCTION()
	void Join();

	UFUNCTION()
	void OnCreateSessionComplete(bool bWasSuccessful);
	void OnSearchSessionComplete(bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& SearchResults);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Type);
	UFUNCTION()
	void OnDestroySessionComplete(bool bWasSuccessful);
};


