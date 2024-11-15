// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeInGameBase.h"

#include "Kismet/GameplayStatics.h"

void AGameModeInGameBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		// set input mode game only
		const FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}

void AGameModeInGameBase::Retry() const
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
