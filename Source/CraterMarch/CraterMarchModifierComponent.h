// =====================================================
// CraterMarchModifierComponent.h
// Purpose: This component handles the Left and Right modifier inputs (Shift keys).
// It is the foundation of the unique combat system - it translates player input into 
// rig control data that other systems (RigControl and Combat) use.
// =====================================================

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CraterMarchModifierComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRATERMARCH_API UCraterMarchModifierComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCraterMarchModifierComponent();

    // ==================================================================
    // Modifier State - These variables are replicated so all players see
    // the same neck movement and posture for fair multiplayer combat
    // ==================================================================
    UPROPERTY(Replicated)
    bool bLeftModifierPressed = false;

    UPROPERTY(Replicated)
    bool bRightModifierPressed = false;

    // Neck turn value: -1.0 = full left, +1.0 = full right, 0.0 = center
    UPROPERTY(Replicated)
    float NeckTurnValue = 0.0f;

    // High Posture is activated when both modifiers are held
    UPROPERTY(Replicated)
    bool bIsHighPosture = false;

    // Helper functions used by RigControlComponent and CombatComponent
    UFUNCTION(BlueprintCallable, Category = "Modifier")
    float GetNeckTurnValue() const { return NeckTurnValue; }

    UFUNCTION(BlueprintCallable, Category = "Modifier")
    bool IsHighPosture() const { return bIsHighPosture; }

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Server-authoritative function called from character input
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_UpdateModifierState(bool bLeft, bool bRight);
};
