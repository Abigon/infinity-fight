// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Core/IF_SaveGameSubsystem.h"
#include "Core/IF_SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/IF_Character.h"

constexpr int32 SlotIndex = 0;
const FString SlotName = "GameSave";

void UIF_SaveGameSubsystem::SaveGame()
{
	if (!GetWorld()) return;
	const auto SaveObject = Cast<UIF_SaveGame>(UGameplayStatics::CreateSaveGameObject(UIF_SaveGame::StaticClass()));
	if (!SaveObject) return;

	const auto Player = Cast<AIF_Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SaveObject->LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	SaveObject->PlayerSaveInfo = Player->GetPlayerSaveInfo();

	UGameplayStatics::SaveGameToSlot(SaveObject, SlotName, SlotIndex);
}

void UIF_SaveGameSubsystem::LoadGame()
{
	CurrentSaveGame = Cast<UIF_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex));
	if (!CurrentSaveGame) return;
}

bool UIF_SaveGameSubsystem::IsHasSave()
{
	return UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex);
}

FString UIF_SaveGameSubsystem::GetLevelNameToLoad() const
{
	return CurrentSaveGame ? CurrentSaveGame->LevelName : "";
}

void UIF_SaveGameSubsystem::UpdatePlayerData(AIF_Character* Player)
{
	if (!CurrentSaveGame) return;
	Player->UpdatePlayerFromSave(CurrentSaveGame->PlayerSaveInfo);
}
