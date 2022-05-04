// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Animations/IF_AnimNotify.h"
#include "Core/IF_BaseCharacter.h"

void UIF_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (!MeshComp) return;
	const auto Char = Cast<AIF_BaseCharacter>(MeshComp->GetOwner());
	if (Char)
	{
		Char->OnAnimNotify(Type);
	}
}

FString UIF_AnimNotify::GetNotifyName_Implementation() const
{
	return Type == EAnimNotifyType::EAT_MAX ? "IF AnimNotify" : UEnum::GetValueAsString(Type);
}
