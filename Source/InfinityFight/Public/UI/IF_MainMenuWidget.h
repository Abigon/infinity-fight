// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IF_MainMenuWidget.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_MainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;
	UPROPERTY(meta = (BindWidget))
	UButton* LoadButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGamePressed();
	UFUNCTION()
	void OnLoadGamePressed();
	UFUNCTION()
	void OnQuitPressed();

	UFUNCTION()
	void OnChangedVisibility(ESlateVisibility InVisibility);
};
