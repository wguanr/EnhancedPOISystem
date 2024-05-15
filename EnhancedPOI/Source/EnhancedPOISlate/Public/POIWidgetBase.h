// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "POIEventInterface.h"
#include "SDefaultPOI.h"
#include "POIWidgetBase.generated.h"



#pragma region EnumerationsAndStructs
//
// UENUM(BlueprintType,meta=(Bitflags))
// enum class EPOIFeaturePreset : uint8
// {
// 	None = 0 UMETA(hidden),
// 	UsingIcon = 1 << 0,
// 	UsingTitle = 1 << 1,
// 	UsingSubtitle = 1 << 2,
// 	UsingDescription = 1 << 3,
// 	UsingBG = 1 << 4
// };


UENUM(BlueprintType)
enum class ETitleShowAnimation : uint8
{
	ETitleOnRight,
	ETitleOnTop
};

UENUM(BlueprintType)
enum class EArrowFeaturePreset : uint8
{
	EShort,
	ELongLine
};


USTRUCT(Blueprintable)
struct FPOIWidgetDefaults
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FText BasicTitleText = FText::FromString(TEXT("MainTitle"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FText SubTitleText = FText::FromString(TEXT("SubTitle"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FText DescriptionText = FText::FromString(TEXT("Description"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FSlateBrush IconImage = FSlateBrush();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FLinearColor ThemeColor = FLinearColor::White;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FSlateBrush BGImage = FSlateBrush();
	

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	ETitleShowAnimation TitleShowAnimation = ETitleShowAnimation::ETitleOnRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	EArrowFeaturePreset ArrowFeatureLevel = EArrowFeaturePreset::EShort;
};



#pragma endregion
/**
 *  give different widget on case
 */

UCLASS()
class ENHANCEDPOISLATE_API UPOIWidgetBase : public UUserWidget ,public IPOIEventInterface
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;
	FPOIWidgetDefaults POIBasicParameters;
	
#pragma region WidgetGeneration
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",meta=(EditCondition="!bCustomCombination",EditConditionHides))
	TEnumAsByte<EPOIFeaturePreset> POIFeatures;

	// 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",meta=(EditCondition="!bCustomCombination",EditConditionHides))
	bool bAllowIconClick = true; // decide using button or border
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",meta=(EditCondition="!bCustomCombination",EditConditionHides))
	bool bAllowTitleClick = true; // decide using button or border
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",meta=(EditCondition="!bCustomCombination",EditConditionHides))
	bool bAllowIconTouch = false; // decide using button or border


	// use custom widget or default widget
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Settings)
	bool bCustomizeCombination;
protected:
	UFUNCTION()
	void GenerateDefaultWidget();
	// UPROPERTY(meta=(BindWidget))
	// class UOverlay* RootWidget;
	
protected:

	// minimal information
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* Title;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* Subtitle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* Icon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* BG;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* AccessoryOfDescription;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UUserWidget* ArrowShort;


	
private:

	bool WidgetFactory();


#pragma endregion

#pragma region SetParams
public:
	bool InitializeBasicParams();



#pragma endregion

#pragma region SetStyles

#pragma endregion


	
#pragma region ShowHideControll
public:
	void SetPoiShowLevel();

	virtual void OnPOIHide_Implementation() override;
	virtual void OnPOIShow_Implementation() override;

	
protected:
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidgetAnim,OptionalWidget=true),Transient) // why transient?
	// UWidgetAnimation* TitleShowRight;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(BindWidgetAnim,OptionalWidget=true),Transient)
	// UWidgetAnimation* TitleShowTop;

private:
	void ShowTitleAnimation();
#pragma endregion
};



