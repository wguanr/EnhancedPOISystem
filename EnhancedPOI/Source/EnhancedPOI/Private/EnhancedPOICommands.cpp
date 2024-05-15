// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnhancedPOICommands.h"

#define LOCTEXT_NAMESPACE "FGrEnhancedPOIModule"

void FEnhancedPOICommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GrEnhancedPOI", "Execute GrEnhancedPOI action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
