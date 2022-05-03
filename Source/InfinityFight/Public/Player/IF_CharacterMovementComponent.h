// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IF_CharacterMovementComponent.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Speed")
	float RunSpeed = 600.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Speed")
	float SprintSpeed = 800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina")
	float MaxStamina = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina")
	float Stamina = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina")
	float StaminaDrainRate = 25.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina")
	float StaminaRestoreRate = 10.f;

public:
	virtual float GetMaxSpeed() const override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMaxStamina(const float NewMaxStamina);

	float GetStaminaPercent() const { return MaxStamina != 0 ? Stamina / MaxStamina : 0.f; }

protected:
	virtual void BeginPlay() override;
};
