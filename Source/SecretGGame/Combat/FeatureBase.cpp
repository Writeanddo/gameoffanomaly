// Fill out your copyright notice in the Description page of Project Settings.


#include "FeatureBase.h"


// Sets default values
AFeatureBase::AFeatureBase(): FCurrentCharge(FCapacity)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFeatureBase::BeginPlay()
{
	Super::BeginPlay();
	if (FRegen > 0.0f)
	{
		GetWorldTimerManager().SetTimer(RegenTimerHandle, this, &AFeatureBase::Regenerate, FRegenTimeStep, true);
	}
}

// Called every frame
void AFeatureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AFeatureBase::Activate()
{
	bQueueFire = true;

	if (bIsOnCooldown)
	{
		return false;
	}

	if (FCurrentCharge <= FCost)
	{
		return false;
	}

	if (!bQueueFire)
	{
		return false;
	}

	FCurrentCharge -= FCost;
	bIsOnCooldown = true;

	OnActivate();
	GetWorldTimerManager().SetTimer(CooldownTimerHandle, this, &AFeatureBase::AfterActivate, FCooldown, false);

	OnFeatureActivated.Broadcast();

	return true;
}

void AFeatureBase::Deactivate()
{
	bQueueFire = false;

	OnFeatureDeactivated.Broadcast();
}

void AFeatureBase::SetTarget(FVector Location, AActor* Actor)
{
	TargetLocation = Location;
	TargetActor = Actor;
	bHasTarget = true;
}

void AFeatureBase::Refill(float Amount)
{
	FCurrentCharge = FMath::Clamp(FCurrentCharge + Amount, 0.0f, FCapacity);
}

void AFeatureBase::RefillFull()
{
	FCurrentCharge = FCapacity;
}

FVector AFeatureBase::GetRandomLocationInRange(FVector const& TargetLocation, float const Range)
{
	FVector const RandomLocation = TargetLocation + FVector(FMath::RandRange(-Range, Range),
	                                                        FMath::RandRange(-Range, Range),
	                                                        FMath::RandRange(-Range, Range));
	return RandomLocation;
}

FVector AFeatureBase::GetLocationAtDistance(FVector const& Origin, FVector const& Target, float const Distance)
{
	FVector const Direction = (Target - Origin).GetSafeNormal();
	FVector const Location = Origin + Direction * Distance;
	return Location;
}

void AFeatureBase::OnActivate_Implementation()
{
	// default implementation
}

void AFeatureBase::AfterActivate()
{
	bIsOnCooldown = false;

	OnFeatureCooldownPassed.Broadcast();

	if (bIsOneShot)
	{
		return;
	}

	if (!bQueueFire)
	{
		return;
	}

	Activate();
}

void AFeatureBase::Regenerate()
{
	if (bIsOnCooldown)
	{
		return;
	}

	FCurrentCharge = FMath::Clamp(FCurrentCharge + FRegen * FRegenTimeStep, 0.0f, FCapacity);
}
