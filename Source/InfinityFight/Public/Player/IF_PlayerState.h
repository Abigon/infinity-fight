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
	int32 TreasuresAmount = 0;
	int32 TotalPoints = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "Treasures")
	FORCEINLINE int32 GetTreasures() const { return TreasuresAmount; }
	void AddTreasures(const int32 Delta);
	
	void AddScore(const int32 DeltaScore);
	FORCEINLINE int32 GetTotalPoints() const { return TotalPoints; }
};
