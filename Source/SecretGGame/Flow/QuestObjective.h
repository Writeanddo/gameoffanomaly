// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestObjective.generated.h"

UENUM(BlueprintType)
enum class EQuestObjectiveIds : uint8
{
	Explore = 0,
	FindKeys = 1,
	AccessAdminConsole = 2,
	DefeatBoss = 3,
	None = 255 UMETA(Hidden)
};


