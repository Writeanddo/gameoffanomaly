﻿// Base class for weapons and abilities.
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat",
		meta = (ToolTip = "If true, fires only once after activation, otherwise fires continuously."))
	bool bIsOneShot = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Total charge capacity."))
	float FCapacity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Cost per activation."))
	float FCost = 10.0f;

	// cooldown in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Cooldown in seconds."))
	float FCooldown = 0.1f;

	// regen in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (ToolTip = "Regeneration in seconds."))
	float FRegen = 0.1f;

	// regen timestep in seconds
	float FRegenTimeStep = 0.1f;

	FTimerHandle CooldownTimerHandle;
	FTimerHandle RegenTimerHandle;

	virtual void Tick(float DeltaTime) override;

	// Start feature activation and return true if successful
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool Activate();

	// Stop feature activation
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Deactivate();

	// Set target location and actor
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetTarget(FVector Location, AActor* Actor);

	// Refill charge
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Refill(float Amount);

	// Refill charge to full
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RefillFull();
	
protected:
	virtual void BeginPlay() override;

	bool bIsOnCooldown = false;
	bool bHasTarget = false;
	bool bQueueFire = false;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	float FCurrentCharge;

	TWeakObjectPtr<AActor> TargetActor;
	FVector TargetLocation;

	// override this function to implement feature activation
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnActivate();
	virtual void OnActivate_Implementation();

private:
	void AfterActivate();
	void Regenerate();
};
