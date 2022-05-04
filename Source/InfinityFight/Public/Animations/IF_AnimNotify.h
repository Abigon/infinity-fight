// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IF_Types.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "IF_AnimNotify.generated.h"

UCLASS()
class INFINITYFIGHT_API UIF_AnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim Notify Interface")
	EAnimNotifyType Type = EAnimNotifyType::EAT_MAX;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
};
