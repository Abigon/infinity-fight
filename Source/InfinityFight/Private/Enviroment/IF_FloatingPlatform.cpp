// Copyright Dmitrii Shukaev. All Rights Reserved.


#include "Enviroment/IF_FloatingPlatform.h"
#include "Kismet/KismetMathLibrary.h"

AIF_FloatingPlatform::AIF_FloatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

void AIF_FloatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetActorLocation();
	EndPoint =  UKismetMathLibrary::TransformLocation(GetActorTransform(), EndPoint);
	StopPlatform();
}

void AIF_FloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMoving)
	{
		PlatformMovement(DeltaTime);
	}
}

void AIF_FloatingPlatform::PlatformMovement(const float DeltaTime)
{
	const FVector InterpLocation = FMath::VInterpTo(GetActorLocation(), EndPoint, DeltaTime, MovementSpeed);
	SetActorLocation(InterpLocation);

	const float DistanceTraveled = (InterpLocation - EndPoint).Size();
	if (DistanceTraveled <= 1.f)
	{
		StopPlatform();
		const FVector Temp = StartPoint;
		StartPoint = EndPoint;
		EndPoint = Temp;
	}
}

void AIF_FloatingPlatform::StopPlatform()
{
	bMoving = false;
	
	FTimerHandle StopTimer;
	GetWorldTimerManager().SetTimer(StopTimer, this, &AIF_FloatingPlatform::PlatformMovementStart, StopTime, false);
}

void AIF_FloatingPlatform::PlatformMovementStart()
{
	bMoving = true;
}
