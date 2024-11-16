// Portal to another level

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SecretGGame/Flow/LevelNames.h"
#include "LevelPortalBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelPortalUnlocked);

UCLASS()
class SECRETGGAME_API ALevelPortalBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelPortalBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Next level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelPortal")
	ELevelNames NextLevel = ELevelNames::None;

	// Locked?
	UPROPERTY(BlueprintReadOnly, Category = "LevelPortal")
	bool bLocked = false;

	// Anomalies required to unlock
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelPortal")
	TArray<class AAnomalyBase*> Anomalies;

	// Autofill with all anomalies in level?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LevelPortal")
	bool bAutoFillAnomalies = false;

	// Unlock portal
	UFUNCTION(BlueprintCallable, Category = "LevelPortal")
	void Unlock();

	// On portal enter
	UFUNCTION(BlueprintCallable, Category = "LevelPortal")
	void EnterPortal();
	
	// On unlock notification
	UPROPERTY(BlueprintAssignable, Category = "LevelPortal")
	FOnLevelPortalUnlocked OnLevelPortalUnlocked;
	
	// assign itself to anomalies in array
	void AssignAnomalies();

	// fill anomalies array with all anomalies in level
	void FillAnomalies();

	// Remove anomaly from array and check if portal can be unlocked
	void RemoveAnomaly(AAnomalyBase* Anomaly);
};
