// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EnhancedPOISlate : ModuleRules
{
	public EnhancedPOISlate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				// "GrEnhancedPOISlate/Public/"
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"ApplicationCore",
				"Engine",
				"InputCore",
				"Slate",
				"UMG",
				"EnhancedPOI"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"ToolMenus",
				"Engine",
				"SlateCore",

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		if (Target.Type == TargetType.Editor)
		{
			PublicDependencyModuleNames.AddRange(
				new string[] {
					"EditorFramework",
					"UnrealEd",
				}
			);
		}
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
