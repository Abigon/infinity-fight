// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Core/IF_GameMode.h"
#include "Core/IF_PlayerController.h"
#include "Player/IF_Character.h"
#include "Player/IF_PlayerState.h"
#include "UI/IF_GameHUD.h"

AIF_GameMode::AIF_GameMode()
{
	PlayerControllerClass = AIF_PlayerController::StaticClass();
	DefaultPawnClass = AIF_Character::StaticClass();
	HUDClass = AIF_GameHUD::StaticClass();
	PlayerStateClass = AIF_PlayerState::StaticClass();
}

void AIF_GameMode::StartPlay()
{
	Super::StartPlay();

	SetGameState(EIFGameState::EGS_InGame);
}

bool AIF_GameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if (PauseSet)
	{
		SetGameState(EIFGameState::EGS_Pause);
	}
	return PauseSet;
}

bool AIF_GameMode::ClearPause()
{
	const auto PauseCleared = Super::ClearPause();
	if (PauseCleared)
	{
		SetGameState(EIFGameState::EGS_InGame);
	}
	return PauseCleared;
}

void AIF_GameMode::SetGameState(const EIFGameState NewState)
{
	if (RFGameState == NewState) return;

	RFGameState = NewState;
	OnGameStateChanged.Broadcast(RFGameState);
}