// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Core/IF_GameMode.h"
#include "Core/IF_PlayerController.h"
#include "Core/IF_SaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
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

void AIF_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	bLoadGame = !UGameplayStatics::ParseOption(Options, "LoadGame").IsEmpty();
}

void AIF_GameMode::StartPlay()
{
	Super::StartPlay();

	const auto Player0 = Cast<AIF_Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Player0)
	{
		Player0->OnPlayerDeath.AddDynamic(this, &AIF_GameMode::KillPlayer);
		if (bLoadGame)
		{
			if (const auto SG = GetGameInstance()->GetSubsystem<UIF_SaveGameSubsystem>())
			{
				SG->UpdatePlayerData(Player0);
			}
		}
	}

	SetGameState(EIFGameState::EGS_InGame);
}

void AIF_GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

void AIF_GameMode::KillPlayer()
{
	SetGameState(EIFGameState::EGS_LooseGame);
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
	if (IFGameState == NewState) return;

	IFGameState = NewState;
	OnGameStateChanged.Broadcast(IFGameState);
}