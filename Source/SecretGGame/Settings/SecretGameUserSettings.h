// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"
#include "RHI.h"
#include "SecretGameUserSettings.generated.h"

// Structure for resolution options
USTRUCT(BlueprintType)
struct FResolutionOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Width;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Selected;
};

// Structure for fullscreen mode options
USTRUCT(BlueprintType)
struct FFullScreenModeOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	// 0: Windowed, 1: Fullscreen, 2: Windowed Fullscreen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Selected;
};

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
	void SetScalabilityLevel(int32 Level);

	static TArray<FResolutionOption> GetCommonFullscreenResolutions();

	UFUNCTION(BlueprintCallable, Category = Settings)
	TArray<FResolutionOption> GetResolutionOptions();

	// given option name and set of options, set screen resoltuion
	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetResolutionOption(const FString& OptionName, const TArray<FResolutionOption>& Options);

	// get fullscreen mode options
	UFUNCTION(BlueprintCallable, Category = Settings)
	TArray<FFullScreenModeOption> GetFullScreenModeOptions();

	// given option name and set of options, set fullscreen mode
	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetFullScreenModeOption(const FString& OptionName, const TArray<FFullScreenModeOption>& Options);

private:
	void ApplyScalabilitySettings()
	{
		SetOverallScalabilityLevel(ScalabilityLevel);
		ApplyResolutionSettings(false);
		SaveSettings();
	}
};

inline void USecretGameUserSettings::SetScalabilityLevel(int32 Level)
{
	ScalabilityLevel = Level;
	ApplyScalabilitySettings();
	ApplyResolutionSettings(false);
}

inline TArray<FResolutionOption> USecretGameUserSettings::GetCommonFullscreenResolutions()
{
	TArray<FResolutionOption> Resolutions;

	// Get available screen resolutions
	if (TArray<FScreenResolutionRHI> ScreenResolutions; RHIGetAvailableResolutions(ScreenResolutions, false))
	{
		for (const FScreenResolutionRHI& Resolution : ScreenResolutions)
		{
			FResolutionOption Option;
			Option.Width = Resolution.Width;
			Option.Height = Resolution.Height;
			Option.Name = FString::Printf(TEXT("%dx%d"), Resolution.Width, Resolution.Height);
			Option.Selected = false;

			Resolutions.Add(Option);
		}
	}

	return Resolutions;
}

inline TArray<FResolutionOption> USecretGameUserSettings::GetResolutionOptions()
{
	// get common resolutions

	TArray<FResolutionOption> Options = GetCommonFullscreenResolutions();

	// Check if the current resolution is in the list
	bool bFound = false;
	for (auto& [Width, Height, Name, Selected] : Options)
	{
		if (Width == GetScreenResolution().X && Height == GetScreenResolution().Y)
		{
			Selected = true;
			bFound = true;
			break;
		}
	}

	// If the current resolution is not in the list, add it
	if (!bFound)
	{
		Options.Add({
			GetScreenResolution().X, GetScreenResolution().Y,
			FString::Printf(TEXT("%dx%d"), GetScreenResolution().X, GetScreenResolution().Y), true
		});
	}

	return Options;
}

inline void USecretGameUserSettings::SetResolutionOption(const FString& OptionName,
                                                         const TArray<FResolutionOption>& Options)
{
	for (const auto& [Width, Height, Name, Selected] : Options)
	{
		if (Name == OptionName)
		{
			SetScreenResolution(FIntPoint(Width, Height));
			ApplyResolutionSettings(false);
			SaveSettings();
			break;
		}
	}
}

inline TArray<FFullScreenModeOption> USecretGameUserSettings::GetFullScreenModeOptions()
{
	TArray<FFullScreenModeOption> Options;

	Options.Add({"Fullscreen", 0, GetFullscreenMode() == EWindowMode::Windowed});
	Options.Add({"Windowed Fullscreen", 1, GetFullscreenMode() == EWindowMode::Fullscreen});
	Options.Add({"Windowed", 2, GetFullscreenMode() == EWindowMode::WindowedFullscreen});

	return Options;
}

inline void USecretGameUserSettings::SetFullScreenModeOption(const FString& OptionName,
                                                             const TArray<FFullScreenModeOption>& Options)
{
	for (const FFullScreenModeOption& Option : Options)
	{
		if (Option.Name == OptionName)
		{
			SetFullscreenMode(static_cast<EWindowMode::Type>(Option.Mode));
			ApplyResolutionSettings(false);
			SaveSettings();
			break;
		}
	}
}
