// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnhancedPOI.h"
#include "EnhancedPOIStyle.h"
#include "EnhancedPOICommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName EnhancedPOITabName("EnhancedPOI");

#define LOCTEXT_NAMESPACE "FEnhancedPOIModule"

void FEnhancedPOIModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEnhancedPOIStyle::Initialize();
	FEnhancedPOIStyle::ReloadTextures();

	FEnhancedPOICommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEnhancedPOICommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FEnhancedPOIModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FEnhancedPOIModule::RegisterMenus));
}

void FEnhancedPOIModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FEnhancedPOIStyle::Shutdown();

	FEnhancedPOICommands::Unregister();
}

void FEnhancedPOIModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FEnhancedPOIModule::PluginButtonClicked()")),
							FText::FromString(TEXT("EnhancedPOI.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FEnhancedPOIModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FEnhancedPOICommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FEnhancedPOICommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEnhancedPOIModule, EnhancedPOI)