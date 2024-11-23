// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomGameInstance.h"
#include "GameFramework/GameMode.h"
#include "GameModeInGameBase.generated.h"

/**
 * 
 */
UCLASS()
class SECRETGGAME_API AGameModeInGameBase : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	// Restart current level
	UFUNCTION(BlueprintCallable, Category = "Game")
	void Retry() const;

	// current GameInstance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	UCustomGameInstance* CustomGameInstance;
	
	// Places player at the start location
	// If GameInstance has previous level - find LevelPortalBase with the same level name as PreviousLevel
	// and set player location to that LevelPortalBase's location
	void PlacePlayerAtStartLocation() const;
};
