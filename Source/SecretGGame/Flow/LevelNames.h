#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELevelNames : uint8
{
	LevelMainMenu = 0 UMETA(DisplayName = "LevelMainMenu"),
	LevelEndGame = 1 UMETA(DisplayName = "LevelEndGame"),
	LevelHubWorld = 2 UMETA(DisplayName = "LevelHubWorld"),

	None = 255 UMETA(Hidden)
};

inline FString GetLevelName(ELevelNames const LevelName)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ELevelNames"), true);

    if (!EnumPtr)
    {
        return FString("Invalid");
    }

    return EnumPtr->GetDisplayNameTextByValue((int64)LevelName).ToString();
}