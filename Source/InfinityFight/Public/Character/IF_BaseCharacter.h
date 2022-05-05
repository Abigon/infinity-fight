// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IF_Types.h"
#include "GameFramework/Character.h"
#include "IF_BaseCharacter.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	class UAnimMontage* DeathMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animations")
	TArray<FMontageInfo> AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;

	bool bPlayingCombatMontage = false;

private:
	float Health = 0.f;

public:
	AIF_BaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetMaxHealth(const float NewMaxHealth);
	void OnAnimNotify(const EAnimNotifyType Type);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, //
		class AController* EventInstigator, AActor* DamageCauser) override;

	float GetHealthPercent() const { return MaxHealth != 0 ? Health / MaxHealth : 0.f; }
	FORCEINLINE bool IsDead() const { return FMath::IsNearlyZero(Health); }

	virtual void PlayImpactFX(const FVector& Location);

protected:
	virtual void BeginPlay() override;

	// vitrual functions for OnAnimNotify
	virtual void AttackEnd();
	virtual void DeadEnd(){};
	virtual void ActivateAttackCollision(){};
	virtual void DeactivateAttackCollision(){};
	virtual void PlaySwingSound(){};

	virtual void PlayAttackMontage();
	virtual void Die(){};

	void ChangeHealth(const float DeltaHealth);
};
