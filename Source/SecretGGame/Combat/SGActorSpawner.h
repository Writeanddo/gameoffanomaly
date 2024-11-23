// Spawn actors in the game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGActorSpawner.generated.h"

UCLASS()
class SECRETGGAME_API ASGActorSpawner : public AActor
{
	GENERATED_BODY()

public:
	ASGActorSpawner();

	// Actor class to spawn
	UPROPERTY(BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Enemy class to spawn."))
	TSubclassOf<AActor> ActorClass;

	// Spawn on begin play?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Spawn on begin play?"))
	bool bSpawnAtBeginPlay = true;

	// Spawn on scanner trigger?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Spawn on scanner trigger?"))
	bool bSpawnOnScannerTrigger = true;

	// Number of times to spawn on scanner trigger
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",
		meta = (ToolTip = "Number of times to spawn on scanner trigger. 0 - infinite."))
	int32 SpawnCount = 0;

	// Scanner trigger chance (0 - 1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",
		meta = (ToolTip = "Scanner trigger chance (0 - 1).", ClampMin = "0.0", ClampMax = "1.0"))
	float ScannerTriggerChance = 0.5f;

	// Reset spawn time throttle
	void ResetSpawnTimeThrottle();

	// Spawn function
	UFUNCTION(BlueprintCallable, Category = "Combat", meta = (ToolTip = "Spawn enemies."))
	void Spawn();

	// Spawn on scanner trigger
	UFUNCTION(BlueprintCallable, Category = "Combat", meta = (ToolTip = "Spawn on scanner trigger."))
	void SpawnOnScannerTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Spawn times remaining
	UPROPERTY(BlueprintReadOnly, Category = "Combat", meta = (ToolTip = "Spawn times remaining."))
	int32 SpawnTimesRemaining = 0;

	// Spawn time throttle time (to prevent spawning too fast)
	float SpawnTimeThrottle = 1.0f;

	// Spawn time throttle timer
	FTimerHandle SpawnTimeThrottleTimerHandle;

public:
	virtual void Tick(float DeltaTime) override;
};
