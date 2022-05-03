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
	EGS_EndGame UMETA(DisplayName = "EndGame"),
	EGS_MAX UMETA(DisplayName = "DefaultMAX")
};
