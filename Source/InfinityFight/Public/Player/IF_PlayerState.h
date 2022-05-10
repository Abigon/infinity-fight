// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "IF_PlayerState.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_PlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	int32 TreasuresAmount = 0.f;

public:
	UFUNCTION(BlueprintCallable, Category = "Treasures")
	FORCEINLINE int32 GetTreasures() const { return TreasuresAmount; }

	void ChangeTreasures(const int32 Delta);
};
