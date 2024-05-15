// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPOIWidget.h"
#include "SDefaultPOI.h"

TSharedRef<SWidget> UDefaultPOIWidget::RebuildWidget()
{
	// Super::RebuildWidget();
	return SAssignNew(SmartPOI,SDefaultPOI)
		.bIconUseButton(true).bSubtitleUseButton(true).bTitleUseButton(true)
		.TitleText(BasicTitleText)
		.POIFeature(POIFeature);
}

void UDefaultPOIWidget::SynchronizeProperties()
{
	// SmartPOI->SetPOIFeature(POIFeature);
	Super::SynchronizeProperties();
	
}

void UDefaultPOIWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	SmartPOI.Reset();
}

FText UDefaultPOIWidget::GetTitle() const
{
	return BasicTitleText;
}

void UDefaultPOIWidget::SetTitle(FText InText)
{
	
}

int32 UDefaultPOIWidget::GetFeatures()
{
	return SmartPOI->GetPOIFeatureEnabled();
}

void UDefaultPOIWidget::EnableFeature(int32 Feature)
{
	POIFeature |= Feature;
}

bool UDefaultPOIWidget::IsFeatureEnabled(int32 Feature) const
{
	
		return (POIFeature & Feature) == Feature;
	
}
