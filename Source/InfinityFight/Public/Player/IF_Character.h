// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/IF_BaseCharacter.h"
#include "IF_Character.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerSprintSignature, bool, bSprinting);

UCLASS()
class INFINITYFIGHT_API AIF_Character : public AIF_BaseCharacter
{
	GENERATED_BODY()

public:
	FOnPlayerDeathSignature OnPlayerDeath;
	FOnPlayerSprintSignature OnPlayerSprint;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate = 65.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate = 65.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName WeaponSocketName = "hand_rSocket";

private:
	bool bAttacking = false;
	bool bPlayingCombatMontage = false;

	UPROPERTY()
	class AIF_Weapon* EquippedWeapon = nullptr;

public:
	AIF_Character(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	void EquipWeapon(class AIF_Weapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void UseHealPotion(const float Value);
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void AddTreasure(const int32 Value);

protected:
	virtual void BeginPlay() override;

	// vitrual functions for OnAnimNotify
	virtual void AttackEnd() override;
	virtual void DeadEnd() override;
	virtual void ActivateAttackCollision() override;
	virtual void DeactivateAttackCollision() override;
	virtual void PlaySwingSound() override;

	virtual void Die() override;

	UFUNCTION(BlueprintCallable, Category = "Test")
	void Test();

private:
	bool CanMove() const;
	bool CanAttack() const;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void SprintStart();
	void SprintEnd();

	void AttackButtonPressed();
	void AttackButtonRealise();
	void Attack();
};
