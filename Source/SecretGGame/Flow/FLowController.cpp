#include "FLowController.h"

#include "Kismet/GameplayStatics.h"

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
	FString const LevelToLoad = GetLevelName(LevelName);
	UE_LOG(LogTemp, Warning, TEXT("Loading level: %s"), *LevelToLoad);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelToLoad));
}
