// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/IF_BaseCharacter.h"
#include "IF_Enemy.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_Enemy : public AIF_BaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* AgroSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USphereComponent* AttackSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* CombatRightCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* CombatLeftCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FName RightSocketName = "RightSocket";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FName LeftSocketName = "LeftSocket";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (Units = "S", ClampMin = 0.f))
	float BackToStartTime = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (Units = "S", ClampMin = 0.f))
	float AttackMinTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (Units = "S", ClampMin = 0.f))
	float AttackMaxTime = 3.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", meta = (Units = "S", ClampMin = 0.f))
	float DeathDelay = 7.f;

private:
	UPROPERTY()
	class AAIController* MyController = nullptr;
	
	UPROPERTY()
	class AIF_Character* Target = nullptr;

	FVector StartLocation;
	bool bCanAttack = false;

	FTimerHandle BackToStartTimer;
	FTimerHandle AttackTimer;
	
public:
	AIF_Enemy();
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;

	// virtual functions for OnAnimNotify
	virtual void AttackEnd() override;
	virtual void ActivateAttackCollision() override;
	virtual void ActivateAttack2Collision() override;
	virtual void DeactivateAttackCollision() override;

	virtual void Die() override;

private:
	void Attack();
	void DoDamage(AActor* OtherActor, FName SocketName);
	void StartAttackTimer();
	void MoveToTarget();
	void BackToStartLocation();

	UFUNCTION()
	virtual void AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	virtual void AttackSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void AttackSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void CombatRightOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void CombatLeftOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
