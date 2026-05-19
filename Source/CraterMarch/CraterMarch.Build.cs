using UnrealBuildTool;

public class CraterMarch : ModuleRules
{
    public CraterMarch(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ControlRig" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
