// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IF_FloorSwitcher.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenDoorSignature, bool, bOpennig);

UCLASS()
class INFINITYFIGHT_API AIF_FloorSwitcher : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Floor Switch")
	FOnOpenDoorSignature OnOpenDoor;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorSwitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch", meta = (Units = "S", ClampMin = 0.f))
	float WaitToRaiseTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	bool CanClose = true;

private:
	FVector InitialSwitchLocation;
	FTimerHandle RaiseTimer;
	bool bIsUsed = false;

public:
	AIF_FloorSwitcher();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, //
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void RaiseFloorSwitch();
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void LowerFloorSwitch();
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateFloorSwitchLocation(const float Z);
};
