// =====================================================
// CraterMarchModifierComponent.cpp
// Purpose: Implementation of the modifier system.
// This handles input processing and ensures all clients see the same neck state.
// =====================================================

#include "CraterMarchModifierComponent.h"
#include "Net/UnrealNetwork.h"

// =====================================================
// Constructor
// =====================================================
UCraterMarchModifierComponent::UCraterMarchModifierComponent()
{
    SetIsReplicatedByDefault(true);
}

// =====================================================
// Replication Setup
// =====================================================
void UCraterMarchModifierComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UCraterMarchModifierComponent, bLeftModifierPressed);
    DOREPLIFETIME(UCraterMarchModifierComponent, bRightModifierPressed);
    DOREPLIFETIME(UCraterMarchModifierComponent, NeckTurnValue);
    DOREPLIFETIME(UCraterMarchModifierComponent, bIsHighPosture);
}

// =====================================================
// Server Update Function
// This is called from the character when the player presses/releases Shift keys
// =====================================================
void UCraterMarchModifierComponent::Server_UpdateModifierState_Implementation(bool bLeft, bool bRight)
{
    bLeftModifierPressed = bLeft;
    bRightModifierPressed = bRight;

    bIsHighPosture = bLeft && bRight;

    // Calculate neck turn value
    if (bLeft && !bRight)
        NeckTurnValue = -1.0f;
    else if (bRight && !bLeft)
        NeckTurnValue = 1.0f;
    else
        NeckTurnValue = 0.0f;
}

bool UCraterMarchModifierComponent::Server_UpdateModifierState_Validate(bool bLeft, bool bRight)
{
    return true;
}
