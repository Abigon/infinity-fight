// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IF_GameInstance.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE FName GetMenuLevelName() const { return MenuLevelName; }
	FORCEINLINE FName GetFirstLevelName() const { return FirstLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MenuLevelName = NAME_None;
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName FirstLevelName = NAME_None;
};
