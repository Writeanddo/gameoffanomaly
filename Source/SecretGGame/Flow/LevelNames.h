#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELevelNames : uint8
{
	LevelMainMenu = 0 UMETA(DisplayName = "LevelMainMenu"),
	LevelEndGame = 1 UMETA(DisplayName = "LevelEndGame"),
	LevelPrologue = 2 UMETA(DisplayName = "LevelPrologue"),
	LevelTutorial = 3 UMETA(DisplayName = "LevelTutorial"),
 	LevelHubWorld = 4 UMETA(DisplayName = "LevelHubWorld"),
	LevelLabWorld1 = 5 UMETA(DisplayName = "LevelLabWorld1"),
	LevelLabWorld2 = 6 UMETA(DisplayName = "LevelLabWorld2"),
	LevelLabWorldFinal = 7 UMETA(DisplayName = "LevelLabWorldFinal"),
	LevelIslands1 = 8 UMETA(DisplayName = "LevelIslands1"),
	LevelIslands2 = 9 UMETA(DisplayName = "LevelIslands2"),
	LevelIslandsFinal = 10 UMETA(DisplayName = "LevelIslandsFinal"),
	LevelTunnels1 = 11 UMETA(DisplayName = "LevelTunnels1"),
	LevelTunnels2 = 12 UMETA(DisplayName = "LevelTunnels2"),
	LevelTunnelsFinal = 13 UMETA(DisplayName = "LevelTunnelsFinal"),
	LevelAdminConsole = 14 UMETA(DisplayName = "LevelAdminConsole"),
	LevelBossFight = 15 UMETA(DisplayName = "LevelBossFight"),
	Count = 16 UMETA(Hidden),
	None = 255 UMETA(Hidden), 
};

// Level name, Enum to string
inline FString GetLevelName(ELevelNames const LevelName)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ELevelNames"), true);

    if (!EnumPtr)
    {
        return FString("Invalid");
    }

    return EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(LevelName)).ToString();
}

// Level name, String to enum
inline ELevelNames GetLevelNameEnum(FString const& LevelName)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ELevelNames"), true);

	if (!EnumPtr)
	{
		return ELevelNames::None;
	}

	for (int i = 0; i < EnumPtr->NumEnums(); i++)
	{
		if (EnumPtr->GetDisplayNameTextByIndex(i).ToString() == LevelName)
		{
			return static_cast<ELevelNames>(i);
		}
	}

	return ELevelNames::None;
}