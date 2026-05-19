// =====================================================
// CraterMarch.h
// Purpose: Main module header file for the CraterMarch project.
// This is required for Unreal Engine to recognize the module.
// =====================================================

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FCraterMarchModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};

IMPLEMENT_PRIMARY_GAME_MODULE(FCraterMarchModule, CraterMarch, "CraterMarch");
