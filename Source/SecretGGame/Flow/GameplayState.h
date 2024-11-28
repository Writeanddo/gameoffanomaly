// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelNames.h"
#include "QuestObjective.h"
#include "Actors/BossKey.h"
#include "UObject/Object.h"
#include "GameplayState.generated.h"

/**
 * 
 */
UCLASS()
class SECRETGGAME_API UGameplayState : public UObject
{
	GENERATED_BODY()
public:

	// Previous level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowController")
	ELevelNames PreviousLevel = ELevelNames::None;

	// Current level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowController")
	ELevelNames CurrentLevel = ELevelNames::None;

	// Acquired boss keys
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowController")
	TArray<EBossKeyNames> AcquiredBossKeys = {};

	// Current objective id
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowController")
	EQuestObjectiveIds CurrentObjectiveId = EQuestObjectiveIds::Explore;
};
