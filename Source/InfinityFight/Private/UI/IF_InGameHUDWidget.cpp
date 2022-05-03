// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "UI/IF_InGameHUDWidget.h"
#include "Player/IF_Character.h"
#include "Player/IF_CharacterMovementComponent.h"

void UIF_InGameHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Player = Cast<AIF_Character>(GetOwningPlayerPawn());
	if (Player)
	{
		CharMovComp = Cast<UIF_CharacterMovementComponent>(Player->GetCharacterMovement()); 
	}
}

float UIF_InGameHUDWidget::GetHealthPercent() const
{
	if (!Player) return 0.f;
	return Player->GetHealthPercent();
}

float UIF_InGameHUDWidget::GetStaminaPercent() const 
{
	if (!CharMovComp) return 0.f;
	return CharMovComp->GetStaminaPercent();
}

FLinearColor UIF_InGameHUDWidget::GetStaminaBarColor() const
{
	if (!CharMovComp) return StaminaBarNormalColor;
	return CharMovComp->IsStaminaBelowMin() ? StaminaBarBelowMinColor : StaminaBarNormalColor;
}
