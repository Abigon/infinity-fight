// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "IF_CharacterMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedSignature, float, StanimaPercent, bool, bIsBelowMin);

UCLASS()
class INFINITYFIGHT_API UIF_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Stamina")
	FOnStaminaChangedSignature OnStaminaChanged;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Speed", meta = (ClampMin = 0.f))
	float RunSpeed = 450.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Speed", meta = (ClampMin = 0.f))
	float SprintSpeed = 700.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina", meta = (ClampMin = 0.f))
	float MaxStamina = 100.f;
	// Use stamina per one second
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina", meta = (ClampMin = 0.f))
	float StaminaDrainRate = 25.f;
	// Restore stamina per one second
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Movement | Stamina", meta = (ClampMin = 0.f))
	float StaminaRestoreRate = 10.f;

private:
	float Stamina = 100.f;

	bool bSprinting = false;
	bool bCanSprint = true;

public:
	virtual float GetMaxSpeed() const override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMaxStamina(const float NewMaxStamina);

	float GetStaminaPercent() const { return MaxStamina != 0 ? Stamina / MaxStamina : 0.f; }
	bool IsStaminaBelowMin() const { return Stamina < StaminaDrainRate; }

protected:
	virtual void BeginPlay() override;

private:
	void CheckStamina(const float DeltaTime);
	void ChangeStamina(const float DeltaStamina);

	bool IsStaminaFull() const { return FMath::IsNearlyEqual(Stamina, MaxStamina); }
	bool IsStaminaEmpty() const { return FMath::IsNearlyZero(Stamina); }

	UFUNCTION()
	void OnSprintStateChange(bool bIsSprint);
};
