// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
};
