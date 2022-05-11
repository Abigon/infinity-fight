// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Player/IF_CharacterMovementComponent.h"
#include "Player/IF_Character.h"

void UIF_CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetMaxStamina(MaxStamina);

	const auto Player = Cast<AIF_Character>(GetPawnOwner());
	if (Player)
	{
		Player->OnPlayerSprint.AddDynamic(this, &UIF_CharacterMovementComponent::OnSprintStateChange);
	}
}

void UIF_CharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckStamina(DeltaTime);
}

float UIF_CharacterMovementComponent::GetMaxSpeed() const
{
	return (bSprinting && bCanSprint) ? SprintSpeed : RunSpeed;
}

void UIF_CharacterMovementComponent::SetMaxStamina(const float NewMaxStamina)
{
	MaxStamina = NewMaxStamina;
	ChangeStamina(MaxStamina);
	bCanSprint = true;
}

void UIF_CharacterMovementComponent::UpdateStaminaFromSave(const float NewStamina, const float NewMaxStamina)
{
	MaxStamina = NewMaxStamina;
	ChangeStamina(NewStamina - NewMaxStamina);
}

void UIF_CharacterMovementComponent::CheckStamina(const float DeltaTime)
{
	const bool IsMove = Velocity.Size() > 0;
	bCanSprint = !IsStaminaEmpty();
	if (bSprinting && IsMove && bCanSprint)
	{
		ChangeStamina(-DeltaTime * StaminaDrainRate);
	}
	else
	{
		if ((!IsMove || !IsStaminaBelowMin()) && !IsStaminaFull())
		{
			ChangeStamina(DeltaTime * StaminaRestoreRate);
		}
	}
}

void UIF_CharacterMovementComponent::ChangeStamina(const float DeltaStamina)
{
	Stamina = FMath::Clamp(Stamina + DeltaStamina, 0.f, MaxStamina);
	OnStaminaChanged.Broadcast(GetStaminaPercent(), IsStaminaBelowMin());
}

void UIF_CharacterMovementComponent::OnSprintStateChange(bool bIsSprint)
{
	bSprinting = bIsSprint;
}
