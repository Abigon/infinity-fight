// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/IF_Item.h"
#include "IF_Weapon.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_Weapon : public AIF_Item
{
	GENERATED_BODY()

protected:
	virtual void OnOverlapExecute(AActor* Actor) override;
};
