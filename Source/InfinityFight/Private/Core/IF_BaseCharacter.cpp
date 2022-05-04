// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Core/IF_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AIF_BaseCharacter::AIF_BaseCharacter(const FObjectInitializer& ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void AIF_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetMaxHealth(MaxHealth);
}

void AIF_BaseCharacter::OnAnimNotify(const EAnimNotifyType Type)
{
	switch (Type)
	{
		case EAnimNotifyType::EAT_WeaponActivate: ActivateAttackCollision(); break;
		case EAnimNotifyType::EAT_WeaponDeactivate: DeactivateAttackCollision(); break;
		case EAnimNotifyType::EAT_WeaponSound: PlaySwingSound(); break;
		case EAnimNotifyType::EAT_AttackEnd: AttackEnd(); break;
		case EAnimNotifyType::EAT_DeadEnd: DeadEnd(); break;
		default: break;
	}
}

void AIF_BaseCharacter::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	Health = MaxHealth;
}

float AIF_BaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float TempDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ChangeHealth(-TempDamage);
	return TempDamage;
}

void AIF_BaseCharacter::ChangeHealth(const float DeltaHealth)
{
	Health = FMath::Clamp(Health + DeltaHealth, 0.f, MaxHealth);
	if (Health <= 0)
	{
		Die();
	}
}

void AIF_BaseCharacter::PlayImpactFX(const FVector& Location)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, Location, FRotator(0.f), false);
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, Location);
}