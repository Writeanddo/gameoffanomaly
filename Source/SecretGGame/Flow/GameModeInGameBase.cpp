// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeInGameBase.h"

#include "CustomGameInstance.h"
#include "EngineUtils.h"
#include "Actors/LevelPortalBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void AGameModeInGameBase::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		const FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;


		CustomGameInstance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance());

		PlacePlayerAtStartLocation();
	}
}

void AGameModeInGameBase::Retry() const
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AGameModeInGameBase::PlacePlayerAtStartLocation() const
{
	if (CustomGameInstance)
	{
		const FName CurrentLevelName = FName(*GetWorld()->GetName());
		const ELevelNames CurrentLevelNameEnum = GetLevelNameEnum(CurrentLevelName.ToString());
		CustomGameInstance->SetCurrentLevel(CurrentLevelNameEnum);

		if (CustomGameInstance->PreviousLevel != ELevelNames::None)
		{
			for (TActorIterator<ALevelPortalBase> PortalItr(GetWorld()); PortalItr; ++PortalItr)
			{
				if (const ALevelPortalBase* LevelPortalBase = *PortalItr; LevelPortalBase->NextLevel ==
					CustomGameInstance->
					PreviousLevel)
				{
					UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(
						LevelPortalBase->GetActorLocation());
					return;
				}
			}
		}
	}
}
