// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IF_MenuFunctionLibrary.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_MenuFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Menu")
	static void OpenMainMenu(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Menu")
	static void OpenFirstLevel(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Menu")
	static bool IsHasSave(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Menu")
	static void SaveGame(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable, Category = "Menu")
	static void LoadGame(const UObject* WorldContextObject);

private:
	static class UIF_GameInstance* GetIF_GameInstanceByObject(const UObject* WorldContextObject);
	static class UIF_SaveGameSubsystem* GetIF_SaveGameSubsystem(const UObject* WorldContextObject);
};
