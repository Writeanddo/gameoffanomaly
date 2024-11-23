// Collectible, that blocks level progression

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalyBase.generated.h"

UCLASS()
class SECRETGGAME_API AAnomalyBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAnomalyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Level portal
	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	class ALevelPortalBase* LevelPortal;

	// is hidden?
	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	bool bAnomalyHidden = true;

	// Reveals anomaly
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void Reveal();

	// Interract with anomaly
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void Interact();

	// Overridable function for custom behavior
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Anomaly")
	void OnInteract();
	virtual void OnInteract_Implementation();

	// Overridable function for custom behavior
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Anomaly")
	void OnReveal();
	virtual void OnReveal_Implementation();


	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
