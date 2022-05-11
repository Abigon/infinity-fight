// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "UI/IF_PauseMenuWidget.h"
#include "Components/Button.h"
#include "Core/IF_MenuFunctionLibrary.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UIF_PauseMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UIF_PauseMenuWidget::OnResumePressed);
	}
	if (LoadButton)
	{
		LoadButton->OnClicked.AddDynamic(this, &UIF_PauseMenuWidget::OnLoadGamePressed);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UIF_PauseMenuWidget::OnMainMenuPressed);
	}
	OnVisibilityChanged.AddDynamic(this, &UIF_PauseMenuWidget::OnChangedVisibility);
}

void UIF_PauseMenuWidget::OnChangedVisibility(ESlateVisibility InVisibility)
{
	if (InVisibility != ESlateVisibility::Visible) return;
	LoadButton->SetIsEnabled(UIF_MenuFunctionLibrary::IsHasSave(this));
}

void UIF_PauseMenuWidget::OnResumePressed()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UIF_PauseMenuWidget::OnLoadGamePressed()
{
	UIF_MenuFunctionLibrary::LoadGame(this);
}

void UIF_PauseMenuWidget::OnMainMenuPressed()
{
	UIF_MenuFunctionLibrary::OpenMainMenu(this);
}
