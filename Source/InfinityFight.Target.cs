// Copyright Dmitrii Shukaev. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class InfinityFightTarget : TargetRules
{
	public InfinityFightTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "InfinityFight" } );
	}
}
