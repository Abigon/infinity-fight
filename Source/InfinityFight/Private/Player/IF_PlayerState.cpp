// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Player/IF_PlayerState.h"

void AIF_PlayerState::AddTreasures(const int32 Delta)
{
	TreasuresAmount = FMath::Clamp(TreasuresAmount + Delta, 0, INT32_MAX);
}

void AIF_PlayerState::AddScore(const int32 DeltaScore)
{
	TotalPoints = FMath::Clamp(TotalPoints + DeltaScore, 0, INT32_MAX);
}
