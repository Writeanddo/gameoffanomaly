// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMODAudioComponent.h"
#include "FMODEvent.h"
#include "GameplayState.h"
#include "LevelNames.h"
#include "Actors/BossKey.h"
#include "QuestObjective.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePlayStateChanged);

constexpr int32 GNum_Boss_Keys = 3;

/**
 * 
 */
UCLASS()
class SECRETGGAME_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Gameplay State
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowController")
	UGameplayState* GameplayState;

	// Set current objective
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void SetCurrentObjectiveId(const EQuestObjectiveIds ObjectiveId) const;

	// Add boss key to acquired keys
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void AddBossKey(EBossKeyNames BossKeyName) const;

	// Has all keys?
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	bool HasAllKeys() const;
	
	// Reset various properties on game start
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void ResetOnGameStart() const;

	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void SetCurrentLevel(const ELevelNames LevelName) const;

	// current to previous level name
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void UpdatePreviousLevel() const;

	// clear previous level
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void ClearPreviousLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "FlowController")
	void UnlockHubLevel() const;
	
	UPROPERTY(BlueprintAssignable, Category = "FlowController",
		meta = (ToolTip = "Fires fields representing player state are changed"))
	FOnGamePlayStateChanged OnGamePlayStateChanged;

	// Override Init method
	virtual void Init() override;

	// FMOD event instance for background music
	UPROPERTY(BlueprintReadOnly, Category = "Audio")
	UFMODAudioComponent* MasterAudioComponent;
};
