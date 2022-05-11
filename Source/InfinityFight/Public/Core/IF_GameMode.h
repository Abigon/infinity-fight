// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IF_Types.h"
#include "IF_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChangedSignature, EIFGameState, GameState);

UCLASS()
class INFINITYFIGHT_API AIF_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Game State")
	FOnGameStateChangedSignature OnGameStateChanged;

private:
	bool bLoadGame = false;

public:
	AIF_GameMode();
	virtual void StartPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

private:
	EIFGameState RFGameState = EIFGameState::EGS_MAX;

	void SetGameState(const EIFGameState NewState);

	UFUNCTION()
	void KillPlayer();
};
