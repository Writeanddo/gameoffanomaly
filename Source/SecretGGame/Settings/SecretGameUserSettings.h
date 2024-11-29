// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SecretGameUserSettings.generated.h"

/**
 * 
 */
UCLASS()
class USecretGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static USecretGameUserSettings* GetUserSettings()
	{
		return Cast<USecretGameUserSettings>(UGameUserSettings::GetGameUserSettings());
	}


    // Sound settings
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Settings,
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MasterVolume = 1.0f;

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetMasterVolume()
	{
		return MasterVolume;
	}

	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetMasterVolume(float Volume)
	{
		MasterVolume = Volume;
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Settings,
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float MusicVolume = 1.0f;

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetMusicVolume()
	{
		return MusicVolume;
	}

	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetMusicVolume(float Volume)
	{
		MusicVolume = Volume;
	}

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Settings,
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float SFXVolume = 1.0f;

	UFUNCTION(BlueprintCallable, Category = Settings)
	float GetSFXVolume()
	{
		return SFXVolume;
	}

	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetSFXVolume(float Volume)
	{
		SFXVolume = Volume;
	}

	// Scalability settings
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Settings,
		meta = (ClampMin = "0", ClampMax = "3", UIMin = "0", UIMax = "3"))
	int32 ScalabilityLevel = 2;

	UFUNCTION(BlueprintCallable, Category = Settings)
	int32 GetScalabilityLevel()
	{
		return ScalabilityLevel;
	}

	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetScalabilityLevel(int32 Level)
	{
		ScalabilityLevel = Level;
		ApplyScalabilitySettings();
	}

private:
	void ApplyScalabilitySettings()
	{
		SetOverallScalabilityLevel(ScalabilityLevel);
		SaveSettings();
	}
};
