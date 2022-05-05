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
	int32 TreaseresAmount = 0.f;

public:
	UFUNCTION(BlueprintCallable, Category = "Treasures")
	FORCEINLINE int32 GetTreasures() const { return TreaseresAmount; }

	void ChangeTreasures(const int32 Delta);
};
