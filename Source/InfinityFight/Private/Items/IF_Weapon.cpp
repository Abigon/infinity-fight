// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Items/IF_Weapon.h"
#include "Core/IF_BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Player/IF_Character.h"
#include "Sound/SoundCue.h"

AIF_Weapon::AIF_Weapon()
{
	CollisionVolume->SetSphereRadius(140.f);
	bRotate = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());

	CombatCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CombatCollision"));
	CombatCollision->SetupAttachment(WeaponMesh);

	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Mesh->DestroyComponent();
}

void AIF_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CombatCollision->OnComponentBeginOverlap.AddDynamic(this, &AIF_Weapon::CombatOnOverlapBegin);
}

void AIF_Weapon::OnOverlapExecute(AActor* Actor)
{
	const auto Char = Cast<AIF_Character>(Actor);
	if (!Char) return;
	Char->EquipWeapon(this);
}

void AIF_Weapon::Equip(AIF_Character* Char)
{
	if (!Char) return;

	SetOwner(Char);
	SetInstigator(Char);
	SpawnOverlapEffects();
	bRotate = false;
	CollisionVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AIF_Weapon::CombatOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Char = Cast<AIF_BaseCharacter>(OtherActor);
	if (!Char) return;

	const FVector HitLocation = WeaponMesh->GetSocketLocation(FXSocketName);
	Char->PlayImpactFX(HitLocation);

	UGameplayStatics::ApplyDamage(Char, Damage, GetInstigatorController(), this, DamageTypeClass);
}

void AIF_Weapon::ActivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AIF_Weapon::DeactivateCollision()
{
	CombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AIF_Weapon::PlaySwingSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, SwingSound, GetActorLocation());
}
