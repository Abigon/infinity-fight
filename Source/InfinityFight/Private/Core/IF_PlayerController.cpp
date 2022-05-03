// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Core/IF_PlayerController.h"
#include "Core/IF_GameMode.h"

AIF_PlayerController::AIF_PlayerController()
{
	bShouldPerformFullTickWhenPaused = true;
}

void AIF_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<AIF_GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddDynamic(this, &AIF_PlayerController::OnGameStateChanged);
		}
	}
}

void AIF_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Pause", IE_Pressed, this, &AIF_PlayerController::OnPauseGame);
}

void AIF_PlayerController::OnPauseGame()
{
	if (!GetWorld()) return;
	const auto GameMode = Cast<AIF_GameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	
	if (IsPaused())
	{
		GameMode->ClearPause();
	}
	else
	{
		GameMode->SetPause(this);
	}
}

void AIF_PlayerController::OnGameStateChanged(const EIFGameState State)
{
	if (State == EIFGameState::EGS_InGame)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeGameAndUI());
		bShowMouseCursor = true;
	}
}