// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IF_Types.h"
#include "GameFramework/HUD.h"
#include "IF_GameHUD.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_GameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InGameHUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> EndGameWidgetClass;

private:
	UPROPERTY()
	TMap<EIFGameState, class UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnGameStateChanged(const EIFGameState NewState);
};
