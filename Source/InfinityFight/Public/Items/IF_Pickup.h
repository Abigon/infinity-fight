// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/IF_Item.h"
#include "IF_Pickup.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_Pickup : public AIF_Item
{
	GENERATED_BODY()

protected:
	virtual void OnOverlapExecute(AActor* Actor) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void OnPickupBP(class AIF_Character* Character);
};
