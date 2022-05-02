// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Enviroment/IF_FloorSwitcher.h"
#include "Components/BoxComponent.h"
#include "Player/IF_Character.h"

AIF_FloorSwitcher::AIF_FloorSwitcher()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	SetRootComponent(TriggerBox);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));

	FloorSwitch = CreateDefaultSubobject<UStaticMeshComponent>("FloorSwitch");
	FloorSwitch->SetupAttachment(GetRootComponent());
}

void AIF_FloorSwitcher::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AIF_FloorSwitcher::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AIF_FloorSwitcher::OnOverlapEnd);

	InitialSwitchLocation = FloorSwitch->GetComponentLocation();
}

void AIF_FloorSwitcher::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!CanClose && bIsUsed) return;
	if (!Cast<AIF_Character>(OtherActor)) return;

	GetWorldTimerManager().ClearTimer(RaiseTimer);
	bIsUsed = true;
	OnOpenDoor.Broadcast(true);
	LowerFloorSwitch();
}

void AIF_FloorSwitcher::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!CanClose) return;
	if (!Cast<AIF_Character>(OtherActor)) return;

	OnOpenDoor.Broadcast(false);
	GetWorldTimerManager().SetTimer(RaiseTimer, this, &AIF_FloorSwitcher::RaiseFloorSwitch, WaitToRaiseTime, false);
}

void AIF_FloorSwitcher::UpdateFloorSwitchLocation(const float Z)
{
	FVector NewLocation = InitialSwitchLocation;
	NewLocation.Z += Z;
	FloorSwitch->SetWorldLocation(NewLocation);
}
