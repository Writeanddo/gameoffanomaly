// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelNames.h"
#include "Actors/BossKey.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SECRETGGAME_API UCustomGameInstance : public UGameInstance
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
	TArray<EBossKeyNames> AcquiredBossKeys;
	
	// Reset various properties on game start
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void ResetOnGameStart()
	{
		PreviousLevel = ELevelNames::None;
		CurrentLevel = ELevelNames::None;
		AcquiredBossKeys.Empty();
	}
	
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void SetCurrentLevel(ELevelNames LevelName)
	{
		CurrentLevel = LevelName;
	}

	// current to previous level name
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void UpdatePreviousLevel()
	{
		PreviousLevel = CurrentLevel;
	}
};
