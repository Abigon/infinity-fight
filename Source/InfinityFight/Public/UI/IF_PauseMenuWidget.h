// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IF_PauseMenuWidget.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_PauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LoadButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnResumePressed();
	UFUNCTION()
	void OnLoadGamePressed();
	UFUNCTION()
	void OnMainMenuPressed();

	UFUNCTION()
	void OnChangedVisibility(ESlateVisibility InVisibility);
};
