// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IF_Types.h"
#include "GameFramework/PlayerController.h"
#include "IF_PlayerController.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AIF_PlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Pause")
	void OnPauseGame();
	UFUNCTION()
	void OnGameStateChanged(const EIFGameState State);
};
