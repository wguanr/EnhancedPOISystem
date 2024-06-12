// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnhancedPOI.h"

#include "Misc/MessageDialog.h"


static const FName EnhancedPOITabName("EnhancedPOI");

#define LOCTEXT_NAMESPACE "FEnhancedPOIModule"

void FEnhancedPOIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	
}

void FEnhancedPOIModule::ShutdownModule()
{

}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEnhancedPOIModule, EnhancedPOI)