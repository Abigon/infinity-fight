// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "UI/IF_GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "Core/IF_GameMode.h"

void AIF_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EIFGameState::EGS_InGame, CreateWidget<UUserWidget>(GetWorld(), InGameHUDWidgetClass));
	GameWidgets.Add(EIFGameState::EGS_Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EIFGameState::EGS_EndGame, CreateWidget<UUserWidget>(GetWorld(), EndGameWidgetClass));

	for (const auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("In GameHUD doesn't setup UserWidget for Game Mode: %s"), *UEnum::GetValueAsString(GameWidgetPair.Key));
		}
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<AIF_GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnGameStateChanged.AddDynamic(this, &AIF_GameHUD::OnGameStateChanged);
		}
	}
}

void AIF_GameHUD::OnGameStateChanged(const EIFGameState NewState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GameWidgets.Contains(NewState))
	{
		CurrentWidget = GameWidgets[NewState];
	}
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
