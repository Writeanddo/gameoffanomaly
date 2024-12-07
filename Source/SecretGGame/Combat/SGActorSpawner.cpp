// Fill out your copyright notice in the Description page of Project Settings.


#include "SGActorSpawner.h"


ASGActorSpawner::ASGActorSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ASGActorSpawner::ResetSpawnTimeThrottle()
{
	GetWorldTimerManager().ClearTimer(SpawnThrottleTimerHandle);
}

bool ASGActorSpawner::Spawn()
{
	if (!ActorClass)
	{
		return false;
	}

	if (GetWorldTimerManager().IsTimerActive(SpawnThrottleTimerHandle) or GetWorldTimerManager().IsTimerActive(
		SpawnDelayTimerHandle))
	{
		return false;
	}

	if (SpawnCount == 0 || SpawnTimesRemaining > 0)
	{
		SpawnTimesRemaining = FMath::Max(0, SpawnTimesRemaining - 1);
	}
	else
	{
		return false;
	}

	if (SpawnDelayTime > 0.0f)
	{
		GetWorldTimerManager().SetTimer(SpawnDelayTimerHandle, this, &ASGActorSpawner::DelayedSpawn,
		                                SpawnDelayTime, false);
	}
	else
	{
		DelayedSpawn();
	}

	GetWorldTimerManager().SetTimer(SpawnThrottleTimerHandle, this, &ASGActorSpawner::ResetSpawnTimeThrottle,
	                                SpawnThrottleTime, false);
	return true;
}

bool ASGActorSpawner::SpawnOnScannerTrigger()
{
	if (!bSpawnOnScannerTrigger)
	{
		return false;
	}

	if (FMath::FRand() <= ScannerTriggerChance)
	{
		return Spawn();
	}

	return false;
}

void ASGActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnTimesRemaining = SpawnCount;

	if (bSpawnAtBeginPlay)
	{
		Spawn();
	}
}

void ASGActorSpawner::DelayedSpawn()
{
	const FVector Location = GetActorLocation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ActorClass, Location, FRotator::ZeroRotator, SpawnParams);
	GetWorldTimerManager().ClearTimer(SpawnDelayTimerHandle);
	OnSuccessfullySpawned.Broadcast();

	if (bSpawnOnScannerTrigger == true)
	{
		if (SpawnCount != 0 and SpawnTimesRemaining == 0)
		{
			OnScannerSpawnsDepleted.Broadcast();
		}
	}
}

void ASGActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
