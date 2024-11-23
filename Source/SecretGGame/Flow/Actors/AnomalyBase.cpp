// Fill out your copyright notice in the Description page of Project Settings.


#include "AnomalyBase.h"

#include "LevelPortalBase.h"


// Sets default values
AAnomalyBase::AAnomalyBase(): LevelPortal(nullptr)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAnomalyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAnomalyBase::Reveal()
{
	bAnomalyHidden = false;
	OnReveal();
}

void AAnomalyBase::Interact()
{
	if (LevelPortal)
	{
		LevelPortal->RemoveAnomaly(this);
	}

	OnInteract();
}

void AAnomalyBase::OnInteract_Implementation()
{
	// Override this function to add custom behavior
}

void AAnomalyBase::OnReveal_Implementation()
{
	// Override this function to add custom behavior
}

// Called every frame
void AAnomalyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
