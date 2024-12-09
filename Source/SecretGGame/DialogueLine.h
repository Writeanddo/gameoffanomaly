// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueLine.generated.h"

UENUM(BlueprintType)
enum class EDialogueActorChoices : uint8
{
	Owner,
	Player,
	None
};


/**
 * 
 */
UCLASS(BlueprintType)
class SECRETGGAME_API UDialogueLine : public UObject
{
	GENERATED_BODY()

public:
	// Text of the line
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	FString Text;

	// Actor talking the line
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	EDialogueActorChoices ActorChoice = EDialogueActorChoices::None;
	
	// Audio file to play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	USoundBase* Audio;

	// Audio offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	float AudioLengthAdjustement = 0.0f;
};