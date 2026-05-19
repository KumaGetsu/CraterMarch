// =====================================================
// CraterMarchRigControlComponent.cpp
// Purpose: Implements real-time bone control using Control Rig.
// This makes the modifier inputs visible as actual neck movement.
// Future expansion: spine bending, tail control, etc.
// =====================================================

#include "CraterMarchRigControlComponent.h"
#include "Components/ControlRigComponent.h"

UCraterMarchRigControlComponent::UCraterMarchRigControlComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCraterMarchRigControlComponent::BeginPlay()
{
    Super::BeginPlay();

    // Create and register the Control Rig component
    ControlRigComp = NewObject<UControlRigComponent>(this);
    ControlRigComp->RegisterComponent();
    ControlRigComp->AttachToComponent(GetOwner()->GetRootComponent(), 
        FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void UCraterMarchRigControlComponent::UpdateRigControls(float NeckTurnValue, bool bHighPosture)
{
    if (!ControlRigComp) return;

    // Neck rotation based on modifier input
    FTransform NeckTransform;
    NeckTransform.SetRotation(FRotator(0.0f, NeckTurnValue * 45.0f, 0.0f).Quaternion());
    ControlRigComp->SetControlTransform(FName("NeckControl"), NeckTransform);

    // High Posture raises the head for better attack positioning
    if (bHighPosture)
    {
        FTransform HighTransform;
        HighTransform.SetRotation(FRotator(-35.0f, NeckTurnValue * 30.0f, 0.0f).Quaternion());
        ControlRigComp->SetControlTransform(FName("HeadControl"), HighTransform);
    }
}        FTransform HighTransform;
        HighTransform.SetRotation(FRotator(-35.0f, NeckTurnValue * 30.0f, 0.0f).Quaternion());
        ControlRigComp->SetControlTransform(FName("HeadControl"), HighTransform);
    }
}
