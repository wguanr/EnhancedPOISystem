// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrPOIModeEditorModeToolkit.h"
#include "GrPOIModeEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "GrPOIModeEditorModeToolkit"

FGrPOIModeEditorModeToolkit::FGrPOIModeEditorModeToolkit()
{
}

void FGrPOIModeEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FGrPOIModeEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FGrPOIModeEditorModeToolkit::GetToolkitFName() const
{
	return FName("GrPOIModeEditorMode");
}

FText FGrPOIModeEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "GrPOIModeEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
