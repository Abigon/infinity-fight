// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Character/IF_AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UIF_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ACharacter>(TryGetPawnOwner());
}

void UIF_AnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (!Character) return;
	Speed = Character->GetVelocity().Size();
	bIsInAir = Character->GetCharacterMovement() ? Character->GetCharacterMovement()->IsFalling() : false;
}