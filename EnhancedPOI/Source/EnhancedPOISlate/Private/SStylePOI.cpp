// Fill out your copyright notice in the Description page of Project Settings.


#include "SStylePOI.h"


FDefaultPOIStyle::FDefaultPOIStyle()
{
}

FDefaultPOIStyle::~FDefaultPOIStyle()
{
}

const FName FDefaultPOIStyle::TypeName(TEXT("FDefaultPOIStyle"));

const FDefaultPOIStyle& FDefaultPOIStyle::GetDefault()
{
	static FDefaultPOIStyle Default;
	return Default;
}

void FDefaultPOIStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
	// add a new simage brush style
	
}
