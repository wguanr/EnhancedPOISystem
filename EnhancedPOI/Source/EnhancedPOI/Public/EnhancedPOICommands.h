// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "EnhancedPOIStyle.h"

class FEnhancedPOICommands : public TCommands<FEnhancedPOICommands>
{
public:

	FEnhancedPOICommands()
		: TCommands<FEnhancedPOICommands>(TEXT("GrEnhancedPOI"), NSLOCTEXT("Contexts", "GrEnhancedPOI", "GrEnhancedPOI Plugin"), NAME_None, FEnhancedPOIStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
