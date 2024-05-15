// Fill out your copyright notice in the Description page of Project Settings.
#include "POIWidgetBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Blueprint/UserWidget.h"

#include "Components/Overlay.h"
#include "Blueprint/WidgetTree.h"
#include "SDefaultPOI.h"


// Sets default values of widget by outer actor
bool UPOIWidgetBase::InitializeBasicParams()
{
	if(POIBasicParameters.BasicTitleText.IsEmpty() || POIBasicParameters.SubTitleText.IsEmpty())
	{
		UE_LOG(LogTemp,Error,TEXT("POI Widget BasicParameters is not set correctly!"));
		return false;
	}
	
	// get sub widget by class
	if(UTextBlock* TBTitleOnRight = Cast<UTextBlock>(Title->GetWidgetFromName(TEXT("MainTitle"))))
	{
		TBTitleOnRight->SetText(POIBasicParameters.BasicTitleText);
	}

	if(UTextBlock* TBSubTitle = Cast<UTextBlock>(Subtitle->GetWidgetFromName(TEXT("SubTitle"))))
	{
		TBSubTitle->SetText(POIBasicParameters.SubTitleText);
	}
	if (UButton* IconButton = Cast<UButton>(Icon->GetWidgetFromName(TEXT("B_Icon"))) )
	{
		FButtonStyle ButtonStyle = FButtonStyle();
		ButtonStyle.Normal = POIBasicParameters.IconImage;
		ButtonStyle.Hovered = POIBasicParameters.IconImage;
		ButtonStyle.Pressed = POIBasicParameters.IconImage;
		ButtonStyle.PressedPadding = FMargin(12,5);
		IconButton->SetStyle(ButtonStyle);
	}

	return true;
}

bool UPOIWidgetBase::WidgetFactory()
{
	if (bCustomizeCombination) // just get the widgets
	{
		Title = Cast<UUserWidget>(GetWidgetFromName(TEXT("Title")));
		Subtitle = Cast<UUserWidget>(GetWidgetFromName(TEXT("Subtitle")));
		Icon = Cast<UUserWidget>(GetWidgetFromName(TEXT("Icon")));
		BG = Cast<UUserWidget>(GetWidgetFromName(TEXT("BG")));
		AccessoryOfDescription = Cast<UUserWidget>(GetWidgetFromName(TEXT("Description")));
		if (Title || Icon)
		{
			return true;
		}
		return false;
	}

	// create widgets : spoidefault
	// SDefaultPOIWidget = SNew(SDefaultPOI)
	// 	.bIconUseButton(bAllowIconClick)
	// 	.bSubtitleUseButton(bAllowTitleClick)
	// 	.bTitleUseButton(bAllowIconTouch)
	// 	.POIFeature(POIFeatures);
	//
	
	GenerateDefaultWidget();
	
	return false;
}


void UPOIWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	// create leaf widgets to match the required parameters
	WidgetFactory();
	// set the widget to SDefaultPOIWidget
	
	

	// if (InitializeBasicParams())
	// {
	// 	SetPoiShowLevel();
	// }
	// else
	// {
	// 	UE_LOG(LogTemp,Error,TEXT("POI Widget is not set correctly!"));
	// }
	
	
}

void UPOIWidgetBase::GenerateDefaultWidget()
{

	// UWidgetBlueprint* WidgetBlueprint = Cast<UWidgetBlueprint>(Cast<UWidgetBlueprintGeneratedClass>(GetClass())->GetPackage()->FindAssetInPackage());
	UE_LOG(LogTemp, Warning, TEXT("GenerateDefaultWidget"));
	UOverlay* RWidget = WidgetTree->ConstructWidget<UOverlay>();
	WidgetTree->RootWidget = RWidget;
	UButton* TitleButton = WidgetTree->ConstructWidget<UButton>();
	TitleButton->SetVisibility(ESlateVisibility::Visible);
	TitleButton->SetStyle(FButtonStyle());
	RWidget->AddChild(TitleButton);
	UTextBlock* TitleText = WidgetTree->ConstructWidget<UTextBlock>();
	TitleText->SetText(FText::FromString(TEXT("Title")));
	TitleButton->AddChild(TitleText);
	TSharedRef<SDefaultPOI> POI = SNew(SDefaultPOI);
	
	
}

#pragma region ShowHideControll

void UPOIWidgetBase::SetPoiShowLevel()
{
	// print current level
	// switch (POIFeatures)
	// {
	// case EPOIFeaturePreset::EIconType:
	// 	Icon->SetVisibility(ESlateVisibility::Visible);
	// 	Title->SetVisibility(ESlateVisibility::Collapsed);
	// 	Subtitle ->SetVisibility(ESlateVisibility::Collapsed);
	// 	break;
	// case EPOIFeaturePreset::ETitleOnly:
	// 	Icon->SetVisibility(ESlateVisibility::Collapsed);
	// 	Title->SetVisibility(ESlateVisibility::Visible);
	// 	Subtitle ->SetVisibility(ESlateVisibility::Collapsed);
	// 	POIBasicParameters.ArrowFeatureLevel = EArrowFeaturePreset::EShort;
	// 	ShowTitleAnimation();
	// 	
	// 	break;
	// case EPOIFeaturePreset::ETitleSubtitle:
	// 	Icon->SetVisibility(ESlateVisibility::Collapsed);
	// 	Title->SetVisibility(ESlateVisibility::Visible);
	// 	Subtitle ->SetVisibility(ESlateVisibility::Visible);
	// 	ShowTitleAnimation();
	// 	break;
	// case EPOIFeaturePreset::EIconTitleSubtitle:
	// 	Icon->SetVisibility(ESlateVisibility::Visible);
	// 	Title->SetVisibility(ESlateVisibility::Visible);
	// 	Subtitle ->SetVisibility(ESlateVisibility::Visible);
	// 	ShowTitleAnimation();
	// case EPOIFeaturePreset::EMax:
	// 	break;
	// default:
	// 	Icon->SetVisibility(ESlateVisibility::Visible);
	// 	Title->SetVisibility(ESlateVisibility::Collapsed);
	// 	Subtitle ->SetVisibility(ESlateVisibility::Collapsed);
	// 	break;
	// 	
	// }

#if WITH_EDITOR
	
	
	Icon->PreConstruct(true);
	Title->PreConstruct(true);
	Subtitle->PreConstruct(true);

#endif
	
}

void UPOIWidgetBase::OnPOIHide_Implementation()
{
	IPOIEventInterface::OnPOIHide_Implementation();

	
}

void UPOIWidgetBase::OnPOIShow_Implementation()
{
	IPOIEventInterface::OnPOIShow_Implementation();
}


void UPOIWidgetBase::ShowTitleAnimation()
{
	if (GWorld->HasBegunPlay())
	{
		switch (POIBasicParameters.TitleShowAnimation)
		{
		case ETitleShowAnimation::ETitleOnRight:
			// PlayAnimation(TitleShowRight);
			break;
		case ETitleShowAnimation::ETitleOnTop:
			// PlayAnimation(TitleShowTop);
			break;
		default:
			break;
		}
	}
	
}
#pragma endregion


