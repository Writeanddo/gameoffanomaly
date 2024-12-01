// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueLine.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SECRETGGAME_API UDialogueLine : public UObject
{
	GENERATED_BODY()

public:
	// name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	FString Name;

	// Text of the line
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	FString Text;

	// Audio file to play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	USoundBase* Audio;
	
};