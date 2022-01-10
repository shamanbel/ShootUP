// The numbers lead a dance

using UnrealBuildTool;

public class ShootUp : ModuleRules
{
	public ShootUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"GameplayTasks",
			"NavigationSystem",
			"PhysicsCore"

		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] 
		{ 
			"ShootUp/Public/Player",
			"ShootUp/Public/Components",
			"ShootUp/Public/Dev",
			"ShootUp/Public/Weapon",
			"ShootUp/Public/UI",
			"ShootUp/Public/Animations",
			"ShootUp/Public/Pickups",
			"ShootUp/Public/Weapon/Components",
			"ShootUp/Public/AI",
			"ShootUp/Public/AI2",
			"ShootUp/Public/AI/Tasks",
			"ShootUp/Public/AI/Services"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
