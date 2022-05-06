// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "IF_SaveGame.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save Game")
	FVector PlayerLocation;
};
