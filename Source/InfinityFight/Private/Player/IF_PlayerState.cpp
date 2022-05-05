// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Player/IF_PlayerState.h"

void AIF_PlayerState::ChangeTreasures(const int32 Delta)
{
	TreaseresAmount = FMath::Clamp(TreaseresAmount - Delta, 0, INT32_MAX);
}
