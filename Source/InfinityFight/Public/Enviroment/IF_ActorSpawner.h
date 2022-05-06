// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IF_ActorSpawner.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_ActorSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	class UBoxComponent* SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	TArray<TSubclassOf<AActor>> SpawnActorClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	class AIF_FloorSwitcher* Switcher = nullptr;

public:
	AIF_ActorSpawner();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SpawnActor(bool bIsOpen);
};
