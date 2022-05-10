// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/IF_Item.h"
#include "IF_Explosion.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_Explosion : public AIF_Item
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion", meta = (Units = "cm", ClampMin = 0.f))
	float DamageRadius = 82.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion", meta = (ClampMin = 0.f))
	float DamageAmount = 15.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion")
	bool DoFullDamage = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Explosion")
	TSubclassOf<UDamageType> ExplosionDamageType = UDamageType::StaticClass();

public:
	AIF_Explosion();

protected:
	virtual void OnOverlapExecute(AActor* Actor) override;
};