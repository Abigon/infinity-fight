// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IF_FloatingPlatform.generated.h"

UCLASS()
class INFINITYFIGHT_API AIF_FloatingPlatform : public AActor
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform", meta = (MakeEditWidget = "true"))
	FVector EndPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MovementSpeed = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform", meta = (Units = "s"))
	float StopTime = 2.f;

private:
	FVector StartPoint = FVector::ZeroVector;
	bool bMoving = false;

public:	
	AIF_FloatingPlatform();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	void PlatformMovement(const float DeltaTime);
	void PlatformMovementStart();
	void StopPlatform();
};
