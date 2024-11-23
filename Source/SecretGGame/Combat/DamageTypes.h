#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EDamageTypes : uint8
{
	Basic = 0 UMETA(DisplayName = "Basic"),
	Overload = 1 UMETA(DisplayName = "Overload"),
};
