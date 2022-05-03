// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IF_Character.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerSprintSignature, bool, bSprinting);

UCLASS()
class INFINITYFIGHT_API AIF_Character : public ACharacter
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	class UAnimMontage* DeathMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	class UAnimMontage* AttackMontage;

private:
	bool bAttacking = false;
	bool bPlayingCombatMontage = false;

	float Health = 0.f;

public:
	AIF_Character(const FObjectInitializer& ObjInit);
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, //
		class AController* EventInstigator, AActor* DamageCauser) override;

	void SetMaxHealth(const float NewMaxHealth)
	{
		MaxHealth = NewMaxHealth;
		Health = MaxHealth;
	}
	float GetHealthPercent() const { return MaxHealth != 0 ? Health / MaxHealth : 0.f; }

	FORCEINLINE bool IsDead() const { return FMath::IsNearlyZero(Health); }

	// Functions will be called from Notifies
	void AttackEnd();

protected:
	virtual void BeginPlay() override;

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

	void ChangeHealth(const float DeltaHealth);
	void Die();
};
