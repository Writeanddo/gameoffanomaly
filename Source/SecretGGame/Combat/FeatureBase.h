// Base class for weapons and abilities.
// Handles cooldowns, cost and regeneration.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FeatureBase.generated.h"

UCLASS()
class SECRETGGAME_API AFeatureBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFeatureBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "If true, fires only once after activation, otherwise fires continuously."))
	bool bIsOneShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Total charge capacity."))
	float FCapacity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Cost per activation."))
	float FCost;

	// cooldown in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Cooldown in seconds."))
	float FCooldown;

	// regen in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Regeneration in seconds."))
	float FRegen;

	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	bool bIsOnCooldown;
	// Remaining charge
	float FCurrentCharge;

	// current target Actor
	AActor* TargetActor;

	// current target location
	FVector TargetLocation;

	// has target?
	bool bHasTarget;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start feature activation and return true if successful
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool Activate();

	//
	// Set target location and actor
	
};
