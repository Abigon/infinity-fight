// Copyright Dmitrii Shukaev. All Rights Reserved.

#include "Enemy/IF_Enemy.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/IF_Character.h"

AIF_Enemy::AIF_Enemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	AgroSphere = CreateDefaultSubobject<USphereComponent>("AgroSphere");
	AgroSphere->SetupAttachment(GetRootComponent());
	AgroSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AgroSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AgroSphere->InitSphereRadius(600.f);

	AttackSphere = CreateDefaultSubobject<USphereComponent>("AttackSphere");
	AttackSphere->SetupAttachment(GetRootComponent());
	AttackSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	AttackSphere->InitSphereRadius(75.f);

	CombatRightCollision = CreateDefaultSubobject<UBoxComponent>("CombatRight");
	CombatRightCollision->SetupAttachment(GetMesh(), RightSocketName);
	CombatRightCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatRightCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatRightCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatRightCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	CombatLeftCollision = CreateDefaultSubobject<UBoxComponent>("CombatLeft");
	CombatLeftCollision->SetupAttachment(GetMesh(), LeftSocketName);
	CombatLeftCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatLeftCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CombatLeftCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CombatLeftCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AIF_Enemy::BeginPlay()
{
	Super::BeginPlay();

	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AIF_Enemy::AgroSphereOnOverlapBegin);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AIF_Enemy::AgroSphereOnOverlapEnd);

	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AIF_Enemy::AttackSphereOnOverlapBegin);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AIF_Enemy::AttackSphereOnOverlapEnd);

	CombatRightCollision->OnComponentBeginOverlap.AddDynamic(this, &AIF_Enemy::CombatRightOnOverlapBegin);
	CombatLeftCollision->OnComponentBeginOverlap.AddDynamic(this, &AIF_Enemy::CombatLeftOnOverlapBegin);

	StartLocation = GetActorLocation();
	MyController = Cast<AAIController>(GetController());
}

void AIF_Enemy::InitControllerOnSpawn()
{
	SpawnDefaultController();
	MyController = Cast<AAIController>(GetController());
}

void AIF_Enemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveToTarget();
}

void AIF_Enemy::AgroSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Char = Cast<AIF_Character>(OtherActor);
	if (!Char || Char->IsDead() || IsDead()) return;
	Target = Char;
	if (MyController)
	{
		MyController->SetFocus(Target);
	}
	GetWorldTimerManager().ClearTimer(BackToStartTimer);
}

void AIF_Enemy::AgroSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto Char = Cast<AIF_Character>(OtherActor);
	if (!Char) return;
	Target = nullptr;
	if (MyController)
	{
		MyController->SetFocus(nullptr);
	}

	GetWorldTimerManager().SetTimer(BackToStartTimer, this, &AIF_Enemy::BackToStartLocation, BackToStartTime, false);
}

void AIF_Enemy::MoveToTarget()
{
	if (!Target) return;

	if (!bCanAttack && MyController)
	{
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalActor(Target);
		MoveRequest.SetAcceptanceRadius(AttackSphere->GetScaledSphereRadius() / 2);
		FNavPathSharedPtr NavPath;
		MyController->MoveTo(MoveRequest, &NavPath);
	}

	if (Target->IsDead())
	{
		GetWorldTimerManager().SetTimer(BackToStartTimer, this, &AIF_Enemy::BackToStartLocation, BackToStartTime, false);
	}
}

void AIF_Enemy::BackToStartLocation()
{
	if (IsDead()) return;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), StartLocation);
}

void AIF_Enemy::AttackSphereOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Char = Cast<AIF_Character>(OtherActor);
	if (!Char) return;

	bCanAttack = true;
	StartAttackTimer();
}

void AIF_Enemy::AttackSphereOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const auto Char = Cast<AIF_Character>(OtherActor);
	if (!Char) return;

	bCanAttack = false;
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void AIF_Enemy::CombatRightOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoDamage(OtherActor, RightSocketName);
}

void AIF_Enemy::CombatLeftOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, //
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoDamage(OtherActor, LeftSocketName);
}

void AIF_Enemy::DoDamage(AActor* OtherActor, FName SocketName)
{
	const auto Char = Cast<AIF_Character>(OtherActor);
	if (!Char) return;

	const FVector HitLocation = GetMesh()->GetSocketLocation(SocketName);
	Char->PlayImpactFX(HitLocation);

	UGameplayStatics::ApplyDamage(Char, Damage, GetController(), this, DamageTypeClass);
}

void AIF_Enemy::StartAttackTimer()
{
	const float AttackTime = FMath::FRandRange(AttackMinTime, AttackMaxTime);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AIF_Enemy::Attack, AttackTime);
}

void AIF_Enemy::Attack()
{
	if (IsDead() || !bCanAttack || !Target) return;
	PlayAttackMontage();
}

void AIF_Enemy::AttackEnd()
{
	Super::AttackEnd();
	if (bCanAttack)
	{
		StartAttackTimer();
	}
}

void AIF_Enemy::ActivateAttackCollision()
{
	Super::ActivateAttackCollision();
	CombatRightCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AIF_Enemy::ActivateAttack2Collision()
{
	Super::ActivateAttack2Collision();
	CombatLeftCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AIF_Enemy::DeactivateAttackCollision()
{
	Super::DeactivateAttackCollision();
	CombatRightCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CombatLeftCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AIF_Enemy::Die()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	StopAnimMontage();
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DeactivateAttackCollision();
	AgroSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLifeSpan(DeathDelay);
}
