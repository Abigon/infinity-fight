// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Core/IF_MenuFunctionLibrary.h"
#include "Core/IF_GameInstance.h"
#include "Core/IF_SaveGame.h"
#include "Core/IF_SaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Player/IF_Character.h"

void UIF_MenuFunctionLibrary::OpenMainMenu(const UObject* WorldContextObject)
{
	const auto MyGameInstance = GetIF_GameInstanceByObject(WorldContextObject);
	if (!MyGameInstance) return;

	if (MyGameInstance->GetMenuLevelName().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Menu level name is NONE"));
		return;
	}
	UGameplayStatics::OpenLevel(WorldContextObject, MyGameInstance->GetMenuLevelName());
}

void UIF_MenuFunctionLibrary::OpenFirstLevel(const UObject* WorldContextObject)
{
	const auto MyGameInstance = GetIF_GameInstanceByObject(WorldContextObject);
	if (!MyGameInstance) return;

	const FName LevelName = MyGameInstance->GetFirstLevelName();
	if (LevelName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Selected Level name is NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(WorldContextObject, LevelName);
}

bool UIF_MenuFunctionLibrary::IsHasSave(const UObject* WorldContextObject)
{
	const auto SGS = GetIF_SaveGameSubsystem(WorldContextObject);
	return SGS ? SGS->IsHasSave() : false;
}

void UIF_MenuFunctionLibrary::SaveGame(const UObject* WorldContextObject)
{
	const auto SGS = GetIF_SaveGameSubsystem(WorldContextObject);
	if (SGS)
	{
		SGS->SaveGame();
	}
}

void UIF_MenuFunctionLibrary::LoadGame(const UObject* WorldContextObject)
{
	const auto SGS = GetIF_SaveGameSubsystem(WorldContextObject);
	if (!SGS) return;
	SGS->LoadGame();
	if (SGS->GetLevelNameToLoad().IsEmpty()) return;
	UGameplayStatics::OpenLevel(WorldContextObject, FName(SGS->GetLevelNameToLoad()), true, "LoadGame=true");
}

UIF_GameInstance* UIF_MenuFunctionLibrary::GetIF_GameInstanceByObject(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World ? World->GetGameInstance<UIF_GameInstance>() : nullptr;
}

UIF_SaveGameSubsystem* UIF_MenuFunctionLibrary::GetIF_SaveGameSubsystem(const UObject* WorldContextObject)
{
	const auto MyGameInstance = GetIF_GameInstanceByObject(WorldContextObject);
	return MyGameInstance ? MyGameInstance->GetSubsystem<UIF_SaveGameSubsystem>() : nullptr;
}
