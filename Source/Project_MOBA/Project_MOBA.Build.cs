// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_MOBA : ModuleRules
{
	public Project_MOBA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "GameplayAbilitiesEditor", "GameplayAbilities",
			"EnhancedInput", "GameplayTasks", "GameplayTags", "UMG", "AIModule", "Niagara", "NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}