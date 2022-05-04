// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/IF_Item.h"
#include "IF_Weapon.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_Weapon : public AIF_Item
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* CombatCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Weapon")
	float Damage = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Weapon")
	TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Weapon")
	USoundCue* SwingSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | Weapon")
	FName FXSocketName = "FXSocket";

public:
	AIF_Weapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void ActivateCollision();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void DeactivateCollision();

	void Equip(class AIF_Character* Char);
	void PlaySwingSound();

protected:
	virtual void BeginPlay() override;

	virtual void OnOverlapExecute(AActor* Actor) override;

	UFUNCTION()
	void CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
