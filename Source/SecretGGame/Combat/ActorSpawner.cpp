// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"


AActorSpawner::AActorSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AActorSpawner::ResetSpawnTimeThrottle()
{
	GetWorldTimerManager().ClearTimer(SpawnTimeThrottleTimerHandle);
}

void AActorSpawner::Spawn()
{
	if (!ActorClass)
	{
		return;
	}

	if (GetWorldTimerManager().IsTimerActive(SpawnTimeThrottleTimerHandle))
	{
		return;
	}

	if (SpawnCount == 0 || SpawnTimesRemaining > 0)
	{
		SpawnTimesRemaining = FMath::Max(0, SpawnTimesRemaining - 1);
	}
	else
	{
		return;
	}

	const FVector Location = GetActorLocation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ActorClass, Location, FRotator::ZeroRotator, SpawnParams);
	GetWorldTimerManager().SetTimer(SpawnTimeThrottleTimerHandle, this, &AActorSpawner::ResetSpawnTimeThrottle,
	                                SpawnTimeThrottle, false);
}

void AActorSpawner::SpawnOnScannerTrigger()
{
	if (!bSpawnOnScannerTrigger)
	{
		return;
	}

	if (FMath::FRand() <= ScannerTriggerChance)
	{
		Spawn();
	}
}

void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnTimesRemaining = SpawnCount;

	if (bSpawnAtBeginPlay)
	{
		Spawn();
	}
}

void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
