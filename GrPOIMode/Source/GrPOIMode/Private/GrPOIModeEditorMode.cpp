// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrPOIModeEditorMode.h"
#include "GrPOIModeEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "GrPOIModeEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/GrPOIModeSimpleTool.h"
#include "Tools/GrPOIModeInteractiveTool.h"

// step 2: register a ToolBuilder in FGrPOIModeEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "GrPOIModeEditorMode"

const FEditorModeID UGrPOIModeEditorMode::EM_GrPOIModeEditorModeId = TEXT("EM_GrPOIModeEditorMode");

FString UGrPOIModeEditorMode::SimpleToolName = TEXT("GrPOIMode_ActorInfoTool");
FString UGrPOIModeEditorMode::InteractiveToolName = TEXT("GrPOIMode_MeasureDistanceTool");


UGrPOIModeEditorMode::UGrPOIModeEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UGrPOIModeEditorMode::EM_GrPOIModeEditorModeId,
		LOCTEXT("ModeName", "GrPOIMode"),
		FSlateIcon(),
		true);
}


UGrPOIModeEditorMode::~UGrPOIModeEditorMode()
{
}


void UGrPOIModeEditorMode::ActorSelectionChangeNotify()
{
}

void UGrPOIModeEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FGrPOIModeEditorModeCommands& SampleToolCommands = FGrPOIModeEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UGrPOIModeSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UGrPOIModeInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UGrPOIModeEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FGrPOIModeEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UGrPOIModeEditorMode::GetModeCommands() const
{
	return FGrPOIModeEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
