// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IF_AnimInstance.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir = false;

private:
	UPROPERTY()
	class ACharacter* Character = nullptr;

public:
	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);
};
