// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Items/IF_Pickup.h"
#include "Player/IF_Character.h"

void AIF_Pickup::OnOverlapExecute(AActor* Actor)
{
	const auto Char = Cast<AIF_Character>(Actor);
	if (Char)
	{
		SpawnOverlapEffects();
		OnPickupBP(Char);
		Destroy();
	}
}
