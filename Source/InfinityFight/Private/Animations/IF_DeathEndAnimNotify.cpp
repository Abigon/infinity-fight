// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Animations/IF_DeathEndAnimNotify.h"

void UIF_DeathEndAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		MeshComp->bNoSkeletonUpdate = true;
		MeshComp->bPauseAnims = true;
	}
}
