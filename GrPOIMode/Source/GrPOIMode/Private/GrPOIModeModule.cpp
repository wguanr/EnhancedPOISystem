// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrPOIModeModule.h"
#include "GrPOIModeEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "GrPOIModeModule"

void FGrPOIModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FGrPOIModeEditorModeCommands::Register();
}

void FGrPOIModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FGrPOIModeEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGrPOIModeModule, GrPOIModeEditorMode)