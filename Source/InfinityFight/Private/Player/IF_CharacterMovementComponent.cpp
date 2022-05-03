// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Player/IF_CharacterMovementComponent.h"
#include "Player/IF_Character.h"

void UIF_CharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIF_CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetMaxStamina(MaxStamina);
}

float UIF_CharacterMovementComponent::GetMaxSpeed() const
{
	const auto* Player = Cast<AIF_Character>(GetPawnOwner());
	return Player && Player->IsSprint() ? SprintSpeed : RunSpeed;
}

void UIF_CharacterMovementComponent::SetMaxStamina(const float NewMaxStamina)
{
	MaxStamina = NewMaxStamina;
	Stamina = MaxStamina;
}
