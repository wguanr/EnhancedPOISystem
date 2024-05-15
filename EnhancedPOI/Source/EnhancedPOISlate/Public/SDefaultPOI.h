// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"

#include "Widgets/SCompoundWidget.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum EPOIFeaturePreset
{
	None = 0 UMETA(hidden),
	UsingIcon = 1 << 0,
	UsingTitle = 1 << 1,
	UsingSubtitle = 1 << 2,
	UsingDescription = 1 << 3,
	UsingBG = 1 << 4
};
ENUM_CLASS_FLAGS(EPOIFeaturePreset);

/**
 *  render and interaction
 */
class ENHANCEDPOISLATE_API SDefaultPOI : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDefaultPOI)
		: _bIconUseButton(true)
		, _bTitleUseButton(true)
		, _bSubtitleUseButton(true)
		, _TitleText(FText::FromString(TEXT("Title")))
		, _SubTitleText(FText::FromString(TEXT("SubTitle")))
		, _DescriptionText(FText::FromString(TEXT("Description")))
		// , _IconImage(FSlateBrush())
		// , _BGImage(FSlateBrush())
		{
		}
		SLATE_ARGUMENT(bool, bIconUseButton)
		SLATE_ARGUMENT(bool, bTitleUseButton)
		SLATE_ARGUMENT(bool, bSubtitleUseButton)
		SLATE_ARGUMENT(FText, TitleText)
		SLATE_ARGUMENT(FText, SubTitleText)
		SLATE_ARGUMENT(FText, DescriptionText)
		// SLATE_ARGUMENT(FSlateBrush&, IconImage)
		// SLATE_ARGUMENT(FSlateBrush&, BGImage)

		SLATE_ARGUMENT(int32, POIFeature)
	SLATE_END_ARGS()



	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	int GetPOIFeatureEnabled() { return POIFeatureEnabled; }
protected:
	
	static int32 POIFeatureEnabled;
	
private:

	static TSharedPtr<SWidget>  GenerateTitle(const FText& TitleText);
	
	static TSharedPtr<SWidget> GenerateSubtitle(const FText& SubTitleText);
	
	static TSharedPtr<SWidget> GenerateIcon( FSlateBrush& IconImage);
	
	static TSharedPtr<SWidget> GenerateBG( FSlateBrush& BGImage);
	
	static TSharedPtr<SWidget> GenerateAccessoryOfDescription(const FText& DescriptionText);
	
	static TSharedPtr<SWidget> GenerateArrow();

public:
	//	FEATURES
	
	//	Toggles the listed features On.
	// UFUNCTION(BlueprintCallable, Category = "Universal Camera Plugin|Features")
	// void EnableFeatures(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/UniversalCameraPlugin.EEnabledFeatures")) int32 FeaturesToEnable);
	// //	Toggles the listed features Off.
	// UFUNCTION(BlueprintCallable, Category = "Universal Camera Plugin|Features")
	// void DisableFeatures(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/UniversalCameraPlugin.EEnabledFeatures")) int32 FeaturesToDisable);
	// //	Returns true if all the tagged features are enabled.
	// UFUNCTION(BlueprintPure, Category = "Universal Camera Plugin|Features")
	// bool AreFeaturesEnabled(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/UniversalCameraPlugin.EEnabledFeatures")) int32 FeaturesToTest);
protected:

};
