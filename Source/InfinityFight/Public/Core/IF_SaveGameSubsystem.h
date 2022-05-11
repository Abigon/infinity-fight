// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IF_SaveGameSubsystem.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_SaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UIF_SaveGame* CurrentSaveGame;

public:
	void SaveGame();
	void LoadGame();
	static bool IsHasSave();
	FString GetLevelNameToLoad() const;

	void UpdatePlayerData(class AIF_Character* Player);
};
