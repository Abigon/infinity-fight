// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IF_MovableDoor.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_MovableDoor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (Units = "S", ClampMin = 0.f))
	float WaitToCloseTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	bool CanClose = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door", meta = (MakeEditWidget = "true"))
	FVector OpenPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	class AIF_FloorSwitcher* Switcher = nullptr;

private:
	FVector InitialDoorLocation;
	FTimerHandle CloseTimer;
	bool bIsUsed = false;

public:
	AIF_MovableDoor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void OpenDoor();
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void CloseDoor();
	UFUNCTION()
	void OnOpenDoor(bool bIsOpen);
	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void UpdateDoorLocation(const float Percent);
};
