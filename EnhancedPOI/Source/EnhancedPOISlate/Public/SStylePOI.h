// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Brushes/SlateImageBrush.h"

#include "SStylePOI.generated.h"

/**
 * 
 */
USTRUCT()
struct ENHANCEDPOISLATE_API FDefaultPOIStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FDefaultPOIStyle();
	virtual ~FDefaultPOIStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FDefaultPOIStyle& GetDefault();


	UPROPERTY(EditAnywhere,Category = Appearance)
	FSlateBrush TemplateImage;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FSlateFontInfo TemplateFont;

	UPROPERTY(EditAnywhere,Category = Appearance)
	FSlateSound TemplateSound;
	
	UPROPERTY(EditAnywhere,Category = Appearance)
	FButtonStyle TemplateButton;
	
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class UDefaultPOIWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FDefaultPOIStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};
