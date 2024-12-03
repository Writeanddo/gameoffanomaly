// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogueQueue.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SECRETGGAME_API UDialogueQueue : public UObject
{
	GENERATED_BODY()

public:
	// Array of dialogue lines
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta=(ExposeOnSpawn = "true"))
	TArray<class UDialogueLine*> DialogueLines;

	// index of cuurent line
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta=(ExposeOnSpawn = "true"))
	int32 CurrentLineIndex = 0;

	// Queue is blocking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta=(ExposeOnSpawn = "true"))
	bool bBlocking = false;
	
	// try getting option and increment index
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	class UDialogueLine* GetNextLine()
	{
		if (CurrentLineIndex < DialogueLines.Num())
		{
			UDialogueLine* Line = DialogueLines[CurrentLineIndex];
			CurrentLineIndex++;
			return Line;
		}
		return nullptr;
	}

	// If there are more lines
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	bool HasNextLine()
	{
		return CurrentLineIndex < DialogueLines.Num();
	}

	// Owner Actor of the queue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue", meta = (ExposeOnSpawn = "true"))
	AActor* OwnerActor;
};
