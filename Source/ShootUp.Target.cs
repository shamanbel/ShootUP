// The numbers lead a dance

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootUpTarget : TargetRules
{
	public ShootUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootUp" } );
	}
}
