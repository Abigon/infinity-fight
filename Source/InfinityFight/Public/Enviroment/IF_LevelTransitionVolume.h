// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IF_LevelTransitionVolume.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_LevelTransitionVolume : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transition")
	class UBoxComponent* TransitionVolume;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Transition")
	class UBillboardComponent* Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transition")
	FName TransitionLevelName;

public:
	AIF_LevelTransitionVolume();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
