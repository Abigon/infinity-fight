// Copyright Dmitrii Shukaev. All Rights Reserved.

#pragma once

//#include "Engine/DataTable.h"
#include "IF_Types.generated.h"

// In Game States. Use for UI
UENUM(Blueprinttype)
enum class EIFGameState : uint8
{
	EGS_InGame UMETA(DisplayName = "InGame"),
	EGS_Pause UMETA(DisplayName = "Pause"),
	EGS_WinGame UMETA(DisplayName = "WinGame"),
	EGS_LooseGame UMETA(DisplayName = "LooseGame"),
	EGS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(Blueprinttype)
enum class EAnimNotifyType : uint8
{
	EAT_WeaponActivate UMETA(DisplayName = "Weapon Activate"),
	EAT_WeaponActivate2 UMETA(DisplayName = "Weapon Activate2"),
	EAT_WeaponDeactivate UMETA(DisplayName = "Weapon Deactivate"),
	EAT_WeaponSound UMETA(DisplayName = "Play Weapon Sound"),
	EAT_AttackEnd UMETA(DisplayName = "Attack End"),
	EAT_MAX UMETA(DisplayName = "DefaultMAX")
};

USTRUCT(BlueprintType)
struct FMontageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (ClampMin = 0.f))
	float Rate = 1.f;
};
