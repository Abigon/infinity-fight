// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "UI/IF_MainMenuWidget.h"
#include "Components/Button.h"
#include "Core/IF_MenuFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UIF_MainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UIF_MainMenuWidget::OnStartGamePressed);
	}
	if (LoadButton)
	{
		LoadButton->OnClicked.AddDynamic(this, &UIF_MainMenuWidget::OnLoadGamePressed);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UIF_MainMenuWidget::OnQuitPressed);
	}
	OnVisibilityChanged.AddDynamic(this, &UIF_MainMenuWidget::OnChangedVisibility);
}

void UIF_MainMenuWidget::OnChangedVisibility(ESlateVisibility InVisibility)
{
	if (InVisibility != ESlateVisibility::Visible) return;
	LoadButton->SetIsEnabled(UIF_MenuFunctionLibrary::IsHasSave(this));
}

void UIF_MainMenuWidget::OnStartGamePressed()
{
	UIF_MenuFunctionLibrary::OpenFirstLevel(this);
}

void UIF_MainMenuWidget::OnLoadGamePressed()
{
	UIF_MenuFunctionLibrary::LoadGame(this);
}

void UIF_MainMenuWidget::OnQuitPressed()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
