// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"

#include "GameplayState.h"


void UCustomGameInstance::SetCurrentObjectiveId(const EQuestObjectiveIds ObjectiveId) const
{
	GameplayState->CurrentObjectiveId = ObjectiveId;
	OnGamePlayStateChanged.Broadcast();
}

void UCustomGameInstance::AddBossKey(const EBossKeyNames BossKeyName) const
{
	GameplayState->AcquiredBossKeys.AddUnique(BossKeyName);

	if (GameplayState->CurrentObjectiveId == EQuestObjectiveIds::Explore)
	{
		SetCurrentObjectiveId(EQuestObjectiveIds::FindKeys);
	}
	
	if (HasAllKeys() && GameplayState->CurrentObjectiveId == EQuestObjectiveIds::FindKeys)
	{
		SetCurrentObjectiveId(EQuestObjectiveIds::DefeatBoss);
	}

	OnGamePlayStateChanged.Broadcast();
}

bool UCustomGameInstance::HasAllKeys() const
{
	return GameplayState->AcquiredBossKeys.Num() == GNum_Boss_Keys;
}

void UCustomGameInstance::ResetOnGameStart() const
{
	GameplayState->PreviousLevel = ELevelNames::None;
	GameplayState->CurrentLevel = ELevelNames::None;
	GameplayState->CurrentObjectiveId = EQuestObjectiveIds::Explore;
	GameplayState->AcquiredBossKeys.Empty();
	OnGamePlayStateChanged.Broadcast();
}

void UCustomGameInstance::SetCurrentLevel(const ELevelNames LevelName) const
{
	GameplayState->CurrentLevel = LevelName;
	OnGamePlayStateChanged.Broadcast();
}

void UCustomGameInstance::UpdatePreviousLevel() const
{
	GameplayState->PreviousLevel = GameplayState->CurrentLevel;
	OnGamePlayStateChanged.Broadcast();
}

void UCustomGameInstance::Init()
{
	Super::Init();
	
	// Create an instance of UGameplayState
	GameplayState = NewObject<UGameplayState>(this, UGameplayState::StaticClass());
}
