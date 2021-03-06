// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Player/IF_Character.h"
#include "Player/IF_PlayerState.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/IF_Weapon.h"
#include "Player/IF_CharacterMovementComponent.h"

AIF_Character::AIF_Character(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UIF_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleSize(48.f, 88.f);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -104.f), FRotator(0.f, -90.f, 0.f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void AIF_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AIF_Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyWeapon();
	Super::EndPlay(EndPlayReason);
}

void AIF_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIF_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AIF_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIF_Character::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AIF_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AIF_Character::LookUpAtRate);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AIF_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AIF_Character::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AIF_Character::SprintEnd);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AIF_Character::AttackButtonPressed);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AIF_Character::AttackButtonRealise);
}

bool AIF_Character::CanMove() const
{
	return !bPlayingCombatMontage && !IsDead();
}

void AIF_Character::MoveForward(float Value)
{
	if (!CanMove() || Value == 0) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AIF_Character::MoveRight(float Value)
{
	if (!CanMove() || Value == 0) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AIF_Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AIF_Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AIF_Character::Jump()
{
	if (CanMove())
	{
		Super::Jump();
	}
}

void AIF_Character::SprintStart()
{
	OnPlayerSprint.Broadcast(true);
}

void AIF_Character::SprintEnd()
{
	OnPlayerSprint.Broadcast(false);
}

void AIF_Character::AttackButtonPressed()
{
	bAttacking = true;
	Attack();
}

void AIF_Character::AttackButtonRealise()
{
	bAttacking = false;
}

void AIF_Character::Attack()
{
	if (!CanAttack()) return;
	PlayAttackMontage();
}

void AIF_Character::AttackEnd()
{
	Super::AttackEnd();
	if (bAttacking)
	{
		Attack();
	}
}

void AIF_Character::ActivateAttackCollision()
{
	Super::ActivateAttackCollision();
	if (EquippedWeapon)
	{
		EquippedWeapon->ActivateCollision();
	}
}

void AIF_Character::DeactivateAttackCollision()
{
	Super::DeactivateAttackCollision();
	if (EquippedWeapon)
	{
		EquippedWeapon->DeactivateCollision();
	}
}

void AIF_Character::PlaySwingSound()
{
	Super::PlaySwingSound();
	if (EquippedWeapon)
	{
		EquippedWeapon->PlaySwingSound();
	}
}

bool AIF_Character::CanAttack() const
{
	return !bPlayingCombatMontage && !IsDead() && EquippedWeapon;
}

void AIF_Character::EquipWeapon(AIF_Weapon* Weapon)
{
	if (!Weapon) return;
	DestroyWeapon();
	Weapon->Equip(this);
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(GetMesh(), AttachmentRules, WeaponSocketName);
	EquippedWeapon = Weapon;
}

void AIF_Character::DestroyWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedWeapon->Destroy();
	}
}

void AIF_Character::Die(AController* InstigatedBy)
{
	StopAnimMontage();
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	OnPlayerDeath.Broadcast();
}

void AIF_Character::UseHealPotion(const float Value)
{
	AddHealth(Value);
}

void AIF_Character::AddTreasures(const int32 Value)
{
	const auto PS = Cast<AIF_PlayerState>(GetPlayerState());
	if (PS)
	{
		PS->AddTreasures(Value);
	}
}

FPlayerSaveInfo AIF_Character::GetPlayerSaveInfo() const
{
	FPlayerSaveInfo PlayerSaveInfo;

	PlayerSaveInfo.MaxHealth = MaxHealth;
	PlayerSaveInfo.Transform = GetActorTransform();

	const auto CM = Cast<UIF_CharacterMovementComponent>(GetMovementComponent());
	if (CM)
	{
		PlayerSaveInfo.MaxStamina = CM->GetMaxStamina();
	}

	const auto MyPlayerState = GetPlayerState<AIF_PlayerState>();
	if (MyPlayerState)
	{
		PlayerSaveInfo.Treasures = MyPlayerState->GetTreasures();
		PlayerSaveInfo.TotalPoints = MyPlayerState->GetTotalPoints();
	}
	return PlayerSaveInfo;
}

void AIF_Character::UpdatePlayerFromSave(const FPlayerSaveInfo& PlayerSaveInfo)
{
	SetActorTransform(PlayerSaveInfo.Transform);
	SetMaxHealth(PlayerSaveInfo.MaxHealth);
	AddTreasures(PlayerSaveInfo.Treasures);
	const auto CM = Cast<UIF_CharacterMovementComponent>(GetMovementComponent());
	if (CM)
	{
		CM->SetMaxStamina(PlayerSaveInfo.MaxStamina);
	}
}

void AIF_Character::Test()
{
	TakeDamage(20.f, FDamageEvent(), nullptr, nullptr);
}
