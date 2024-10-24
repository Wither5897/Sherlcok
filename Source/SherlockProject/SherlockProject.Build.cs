// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SherlockProject : ModuleRules
{
	public SherlockProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "OnlineSubsystem", "OnlineSubsystemSteam", "Networking", "UMG" });
        
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}
