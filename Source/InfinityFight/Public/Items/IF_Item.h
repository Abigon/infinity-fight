// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IF_Item.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_Item : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class USphereComponent* CollisionVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UParticleSystemComponent* IdleParticlesComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | FX")
	class UParticleSystem* OverlapParticles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | FX")
	class USoundCue* OverlapSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | FX")
	bool bRotate = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item | FX")
	float RotationRate = 45.f;

public:
	AIF_Item();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnOverlapEffects();

	virtual void OnOverlapExecute(AActor* Actor){};
};
