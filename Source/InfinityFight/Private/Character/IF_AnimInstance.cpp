// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Character/IF_AnimInstance.h"
#include "Character/IF_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UIF_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AIF_BaseCharacter>(TryGetPawnOwner());
}

void UIF_AnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (!Character) return;
	Speed = Character->GetVelocity().Size();
	bIsInAir = Character->GetCharacterMovement() ? Character->GetCharacterMovement()->IsFalling() : false;
	bIsDead = Character->IsDead();
}