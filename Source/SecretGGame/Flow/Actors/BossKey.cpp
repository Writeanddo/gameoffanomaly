// Fill out your copyright notice in the Description page of Project Settings.


#include "BossKey.h"

#include "SecretGGame/Flow/CustomGameInstance.h"


class UCustomGameInstance;
// Sets default values
ABossKey::ABossKey()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABossKey::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABossKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABossKey::Pickup()
{
	if (!bPickedUp and BossKeyName != EBossKeyNames::None)
	{
		bPickedUp = true;

		if (UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
		{
			GameInstance->AcquiredBossKeys.AddUnique(BossKeyName);
		}

		OnPickup.Broadcast();
	}
}
