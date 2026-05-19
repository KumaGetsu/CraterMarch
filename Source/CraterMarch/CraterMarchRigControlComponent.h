// =====================================================
// CraterMarchRigControlComponent.h
// Purpose: Dynamic bone control using Control Rig.
// Currently focused on neck control but designed to be expanded for spine, tail, and other attack types in the future.
// This component receives data from ModifierComponent and applies it to the skeleton.
// =====================================================

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CraterMarchRigControlComponent.generated.h"

class UControlRigComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRATERMARCH_API UCraterMarchRigControlComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCraterMarchRigControlComponent();

    // The Control Rig that manipulates bones in real time
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control Rig")
    UControlRigComponent* ControlRigComp;

    // Main update function called every frame from the character
    UFUNCTION(BlueprintCallable, Category = "Rig Control")
    void UpdateRigControls(float NeckTurnValue, bool bHighPosture);

protected:
    virtual void BeginPlay() override;
};
