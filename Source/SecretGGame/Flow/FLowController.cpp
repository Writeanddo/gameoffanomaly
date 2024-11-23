#include "FLowController.h"

#include "CustomGameInstance.h"
#include "Kismet/GameplayStatics.h"

class UCustomGameInstance;

UFLowController::UFLowController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Constructor implementation
}


UWorld* UFLowController::GetWorld()
{
#if WITH_EDITOR
	if (GIsEditor)
	{
		return GWorld;
	}
#endif // WITH_EDITOR
	return GEngine->GetWorldContexts()[0].World();
}


void UFLowController::LoadLevel(ELevelNames const LevelName)
{
	if (UCustomGameInstance* CustomGameInstance = Cast<UCustomGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (LevelName == ELevelNames::LevelPrologue)
		{
			CustomGameInstance->ResetOnGameStart();
		}
		else if (LevelName != ELevelNames::LevelMainMenu || LevelName != ELevelNames::None || LevelName != ELevelNames::LevelEndGame)
		{
			CustomGameInstance->UpdatePreviousLevel();
		}
	}

	FString const LevelToLoad = GetLevelName(LevelName);
	UE_LOG(LogTemp, Warning, TEXT("Loading level: %s"), *LevelToLoad);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelToLoad));
}
