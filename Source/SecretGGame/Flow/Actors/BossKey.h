// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickup);

UENUM(BlueprintType)
enum class EBossKeyNames : uint8
{
	KeyLabWorld = 0 UMETA(DisplayName = "KeyLabWorld"),
	KeyIslands = 1 UMETA(DisplayName = "KeyIslands"),
	KeyTunnels = 2 UMETA(DisplayName = "KeyTunnels"),

	None = 255 UMETA(Hidden)
};


UCLASS()
class SECRETGGAME_API ABossKey : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	bool bPickedUp = false;
	
	// Boss key name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossKey")
	EBossKeyNames BossKeyName = EBossKeyNames::None;

	// Pickup function
	UFUNCTION(BlueprintCallable, Category = "BossKey")
	void Pickup();
	
	// Onpickup notifier
	UPROPERTY(BlueprintAssignable, Category = "Events", meta = (ToolTip = "Fires when key is picked up."))
	FOnPickup OnPickup;
};
