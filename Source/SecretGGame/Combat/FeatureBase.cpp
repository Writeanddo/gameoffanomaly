// Fill out your copyright notice in the Description page of Project Settings.


#include "FeatureBase.h"


// Sets default values
AFeatureBase::AFeatureBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFeatureBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFeatureBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

