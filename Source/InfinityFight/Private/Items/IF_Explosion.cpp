// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Items/IF_Explosion.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AIF_Explosion::AIF_Explosion()
{
	CollisionVolume->SetSphereRadius(82.f);
}

void AIF_Explosion::OnOverlapExecute(AActor* Actor)
{
	if (!Actor || !GetWorld()) return;

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, //
		ExplosionDamageType, {}, this, nullptr, DoFullDamage);

	SpawnOverlapEffects();

	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.f);
	Destroy();
}
