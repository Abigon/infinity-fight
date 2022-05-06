// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Enviroment/IF_ActorSpawner.h"
#include "Enviroment/IF_FloorSwitcher.h"
#include "Components/BoxComponent.h"
#include "Enemy/IF_Enemy.h"
#include "Kismet/KismetMathLibrary.h"

AIF_ActorSpawner::AIF_ActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawningBox = CreateDefaultSubobject<UBoxComponent>("SpawningBox");
	SetRootComponent(SpawningBox);
}

void AIF_ActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (Switcher)
	{
		Switcher->OnOpenDoor.AddDynamic(this, &AIF_ActorSpawner::SpawnActor);
	}
	else
	{
		SpawnActor(false);
	}
}

void AIF_ActorSpawner::SpawnActor(bool bIsOpen)
{
	if (!GetWorld() || SpawnActorClasses.Num() == 0) return;

	const int32 Index = FMath::RandRange(0, SpawnActorClasses.Num() - 1);
	if (!SpawnActorClasses[Index]) return;

	const FVector SpawnPoint = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawningBox->GetScaledBoxExtent());
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const auto Enemy = Cast<AIF_Enemy>(GetWorld()->SpawnActor<AActor>(SpawnActorClasses[Index], SpawnPoint, FRotator(0), SpawnParams));
	if (Enemy)
	{
		Enemy->InitControllerOnSpawn();
	}
}