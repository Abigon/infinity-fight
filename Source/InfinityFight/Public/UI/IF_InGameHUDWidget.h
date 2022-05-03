// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IF_InGameHUDWidget.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_InGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Stamina")
	FLinearColor StaminaBarNormalColor = FLinearColor(0.f, 0.5f, 1.f, 1.f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Stamina")
	FLinearColor StaminaBarBelowMinColor = FLinearColor(1.f, 0.2f, 0.f, 1.f);;
	
private:
	UPROPERTY()
	class AIF_Character* Player = nullptr;

	UPROPERTY()
	class UIF_CharacterMovementComponent* CharMovComp = nullptr;

	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetStaminaPercent() const;
	UFUNCTION(BlueprintCallable, Category = "UI")
	FLinearColor GetStaminaBarColor() const;
};
