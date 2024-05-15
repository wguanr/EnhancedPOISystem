// Fill out your copyright notice in the Description page of Project Settings.


#include "SDefaultPOI.h"

#include "SlateOptMacros.h"


int32 SDefaultPOI::POIFeatureEnabled = 0; //??????

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDefaultPOI::Construct(const FArguments& InArgs)
{
	POIFeatureEnabled = InArgs._POIFeature;

	
	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SVerticalBox)
			
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				GenerateTitle(InArgs._TitleText).ToSharedRef()
					
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				GenerateSubtitle(InArgs._SubTitleText).ToSharedRef()
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				GenerateAccessoryOfDescription(InArgs._DescriptionText).ToSharedRef()
			]
			
		]
		// + SOverlay::Slot()
		// .HAlign(HAlign_Center)
		// .VAlign(VAlign_Center)
		//
		// [
		// 	GenerateBG(InArgs._BGImage).ToSharedRef()
		// ]
	];
	
}



#pragma region GenerateWidget

//todo : set styles

TSharedPtr<SWidget> SDefaultPOI::GenerateTitle(const FText& TitleText)
{
	// set to a SNullWidget
	TSharedPtr<SWidget> TitleWidget = SNullWidget::NullWidget;
	if (POIFeatureEnabled & UsingTitle)
	{
		
		TitleWidget = SNew(STextBlock)
		.Font(FAppStyle::Get().GetFontStyle("Roboto"))
		.Justification(ETextJustify::Left)
		.Margin(FMargin(5, 0, 5, 0))
		.Text(TitleText);
	}
	

	return TitleWidget;
}

TSharedPtr<SWidget> SDefaultPOI::GenerateSubtitle(const FText& SubTitleText)
{
	TSharedPtr<SWidget> SubTitleWidget = SNullWidget::NullWidget;
	if (POIFeatureEnabled & UsingSubtitle)
	{
		SubTitleWidget =
	SNew(STextBlock)
		.Font(FAppStyle::Get().GetFontStyle("Roboto"))
		.Justification(ETextJustify::Left)
		.Margin(FMargin(5, 0, 5, 5))
		.Text(SubTitleText)
		.ColorAndOpacity(FColor(.5, .5, .5));
	}
		return SubTitleWidget;
}

TSharedPtr<SWidget> SDefaultPOI::GenerateIcon(FSlateBrush& IconImage)
{
	TSharedPtr<SWidget> IconWidget = SNullWidget::NullWidget;
	if (POIFeatureEnabled & UsingIcon)
	{
		// FButtonStyle* ButtonStyle = new FButtonStyle();
		IconWidget = SNew(SButton)
			.ButtonStyle(FCoreStyle::Get(), "NoBorder")
			.ContentPadding(FMargin(0))
			// .ButtonStyle(ButtonStyle)
			.OnClicked(FOnClicked::CreateLambda([]() { return FReply::Handled(); }))
			;
	}
	return IconWidget;
}

TSharedPtr<SWidget> SDefaultPOI::GenerateBG(FSlateBrush& BGImage)
{
	return SNew(SImage)
		// .Image(BGImage)
		;
}

TSharedPtr<SWidget> SDefaultPOI::GenerateAccessoryOfDescription(const FText& DescriptionText)
{
	TSharedPtr<SWidget> DescriptionWidget = SNullWidget::NullWidget;
	if (POIFeatureEnabled & UsingDescription)
	{
		DescriptionWidget =
		SNew(STextBlock)
        		.Font(FAppStyle::Get().GetFontStyle("Roboto"))
        		.Justification(ETextJustify::Left)
        		.Margin(FMargin(5, 0, 5, 0))
        		.Text(DescriptionText)
        		.ColorAndOpacity(FColor(.5, .5, .5));
	}
	return DescriptionWidget;
	
}

TSharedPtr<SWidget> SDefaultPOI::GenerateArrow()
{
	return SNew(SImage)
		.Image(FCoreStyle::Get().GetBrush("ToolPanel.GroupBorder"));
	
}

#pragma endregion

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
