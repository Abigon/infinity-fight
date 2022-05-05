// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Enviroment/IF_LevelTransitionVolume.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/IF_Character.h"

AIF_LevelTransitionVolume::AIF_LevelTransitionVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	TransitionVolume = CreateDefaultSubobject<UBoxComponent>("TransitionVolume");
	SetRootComponent(TransitionVolume);

	Billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
	Billboard->SetupAttachment(GetRootComponent());
}

void AIF_LevelTransitionVolume::BeginPlay()
{
	Super::BeginPlay();

	TransitionVolume->OnComponentBeginOverlap.AddDynamic(this, &AIF_LevelTransitionVolume::OnOverlapBegin);
}

void AIF_LevelTransitionVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Cast<AIF_Character>(OtherActor) || !GetWorld() || TransitionLevelName == NAME_None) return;

	// TODO: save game
	UGameplayStatics::OpenLevel(GetWorld(), TransitionLevelName);
}
