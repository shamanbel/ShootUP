// The numbers lead a dance

using UnrealBuildTool;
using System.Collections.Generic;

public class ShootUpEditorTarget : TargetRules
{
	public ShootUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ShootUp" } );
	}
}
