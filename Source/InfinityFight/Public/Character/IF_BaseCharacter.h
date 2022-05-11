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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (ClampMin = 0.f))
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TArray<FMontageInfo> AttackMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class UParticleSystem* HitParticles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USoundCue* HitSound;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (Units = "%", ClampMin = 0, ClampMax = 100, UIMin = 0, UIMax = 100))
	int32 ReactOnHitProbability = 50;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* ReactMontage;

	bool bPlayingCombatMontage = false;

private:
	float Health = 100.f;

public:
	AIF_BaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void SetMaxHealth(const float NewMaxHealth);
	void OnAnimNotify(const EAnimNotifyType Type);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, //
		class AController* EventInstigator, AActor* DamageCauser) override;

	float GetHealthPercent() const { return MaxHealth != 0 ? Health / MaxHealth : 0.f; }
	FORCEINLINE bool IsDead() const { return FMath::IsNearlyZero(Health); }
	FORCEINLINE float GetHealth() const { return Health; }

	virtual void PlayImpactFX(const FVector& Location);

protected:
	virtual void BeginPlay() override;

	// virtual functions for OnAnimNotify
	virtual void AttackEnd();
	virtual void ActivateAttackCollision(){};
	virtual void ActivateAttack2Collision(){};
	virtual void DeactivateAttackCollision(){};
	virtual void PlaySwingSound(){};

	virtual void PlayAttackMontage();
	virtual void Die(){};
	virtual void DamageReact();

	void ChangeHealth(const float DeltaHealth);
};
