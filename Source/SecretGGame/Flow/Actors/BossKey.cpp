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

	if (const UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
	{
		if (GameInstance->GameplayState->AcquiredBossKeys.Contains(BossKeyName))
		{
			Destroy();
		}
	}
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

		if (const UCustomGameInstance* GameInstance = Cast<UCustomGameInstance>(GetGameInstance()))
		{
			GameInstance->AddBossKey(BossKeyName);
		}

		OnPickup.Broadcast();
	}
}
