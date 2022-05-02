// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Enviroment/IF_MovableDoor.h"
#include "Enviroment/IF_FloorSwitcher.h"
#include "Kismet/KismetMathLibrary.h"

AIF_MovableDoor::AIF_MovableDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	SetRootComponent(DoorMesh);
}

void AIF_MovableDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialDoorLocation = GetActorLocation();
	OpenPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), OpenPoint);
	if (Switcher)
	{
		Switcher->OnOpenDoor.AddDynamic(this, &AIF_MovableDoor::OnOpenDoor);
	}
}

void AIF_MovableDoor::OnOpenDoor(bool bIsOpen)
{
	if (!CanClose && bIsUsed) return;
	if (bIsOpen)
	{
		bIsUsed = true;
		OpenDoor();
	}
	else
	{
		GetWorldTimerManager().SetTimer(CloseTimer, this, &AIF_MovableDoor::CloseDoor, WaitToCloseTime, false);
	}
}

void AIF_MovableDoor::UpdateDoorLocation(const float Percent)
{
	const FVector CurrentLoc = FMath::Lerp(InitialDoorLocation, OpenPoint, Percent);
	SetActorLocation(CurrentLoc);
}
