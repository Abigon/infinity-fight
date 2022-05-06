// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "UI/IF_MainMenuWidget.h"
#include "Components/Button.h"
#include "Core/IF_GameInstance.h"
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
	LoadButton->SetIsEnabled(false);
}

void UIF_MainMenuWidget::OnStartGamePressed()
{
	if (!GetWorld()) return;

	const auto STUGameInstance = GetWorld()->GetGameInstance<UIF_GameInstance>();
	if (!STUGameInstance) return;

	if (STUGameInstance->GetFirstLevelName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("First level name is NONE"));
		return;
	}
	UGameplayStatics::OpenLevel(this, STUGameInstance->GetFirstLevelName());
}

void UIF_MainMenuWidget::OnLoadGamePressed() {}

void UIF_MainMenuWidget::OnQuitPressed()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
