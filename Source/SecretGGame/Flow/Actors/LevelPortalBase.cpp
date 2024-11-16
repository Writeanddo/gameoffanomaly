// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPortalBase.h"

#include "AnomalyBase.h"
#include "EngineUtils.h"
#include "SecretGGame/Flow/FLowController.h"


// Sets default values
ALevelPortalBase::ALevelPortalBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelPortalBase::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoFillAnomalies)
	{
		FillAnomalies();
	}
	AssignAnomalies();
}

// Called every frame
void ALevelPortalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelPortalBase::Unlock()
{
	bLocked = false;
	OnLevelPortalUnlocked.Broadcast();
}

void ALevelPortalBase::EnterPortal()
{
	if (bLocked)
	{
		return;
	}

	if (NextLevel != ELevelNames::None)
	{
		UFLowController::LoadLevel(NextLevel);
	}
}


void ALevelPortalBase::AssignAnomalies()
{
	for (AAnomalyBase* Anomaly : Anomalies)
	{
		Anomaly->LevelPortal = this;
	}
}

void ALevelPortalBase::FillAnomalies()
{
	if (bAutoFillAnomalies)
	{
		for (TActorIterator<AAnomalyBase> AnomalyItr(GetWorld()); AnomalyItr; ++AnomalyItr)
		{
			AAnomalyBase* Anomaly = *AnomalyItr;
			Anomalies.Add(Anomaly);
		}
	}
}


void ALevelPortalBase::RemoveAnomaly(AAnomalyBase* Anomaly)
{
	Anomalies.Remove(Anomaly);
	if (Anomalies.Num() == 0)
	{
		Unlock();
	}
}
