// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "CoreMinimal.h"
#include "Components/Widget.h"
#include "SDefaultPOI.h"
#include "DefaultPOIWidget.generated.h"


class UImage;



/**
 * 
 */
UCLASS(ClassGroup = UI ,Blueprintable,BlueprintType,meta=(Category = "POI"))
class ENHANCEDPOISLATE_API UDefaultPOIWidget : public UWidget
{
	GENERATED_BODY()

protected:

	
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override ;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override {							//在编辑器上的控件分类
		return FText::FromString("POI");
	}
#endif

public:



	UFUNCTION(BlueprintCallable)		//公开函数到蓝图
	FText GetTitle() const;
	UFUNCTION(BlueprintCallable)
	void SetTitle(FText InText) ;

	UFUNCTION(BlueprintCallable)
	int32 GetFeatures();
	UFUNCTION(BlueprintCallable)
	void EnableFeature(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/EnhancedPOISlate.EPOIFeaturePreset")) int32 Feature);
protected:

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",meta=(Bitmask, BitmaskEnum = "/Script/EnhancedPOISlate.EPOIFeaturePreset") )
	int32 POIFeature = 31;
	UFUNCTION(BlueprintCallable,Category="POI | Basic")
	bool IsFeatureEnabled(UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/EnhancedPOISlate.EPOIFeaturePreset")) int32 Feature) const;

	UPROPERTY(EditAnywhere, BlueprintGetter = "GetTitle", BlueprintSetter = "SetTitle",BlueprintReadWrite,Category="POI | Basic",
		meta = (EditCondition = "POIFeature",EditConditionHides))
	FText BasicTitleText = FText::FromString(TEXT("MainTitle"));
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",
		meta = (EditCondition = "POIFeature",EditConditionHides))
	FText SubTitleText = FText::FromString(TEXT("SubTitle"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",
		meta = (EditCondition = "POIFeature ",EditConditionHides))
	FText DescriptionText = FText::FromString(TEXT("Description"));
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",
		meta = (EditCondition = "POIFeature ",EditConditionHides))
	UImage* IconImage ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic")
	FLinearColor ThemeColor = FLinearColor::White;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="POI | Basic",
		meta = (EditCondition = "POIFeature",EditConditionHides))
	UImage* BGImage ;
	//公开属性到编辑器
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool bAllowIconClick = true; // decide using button or border
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool bAllowTitleClick = true; // decide using button or border
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Default)
	bool bAllowIconTouch = false; // decide using button or border

	TSharedPtr<class SDefaultPOI> SmartPOI;	//实际的Slate控件
	
};
