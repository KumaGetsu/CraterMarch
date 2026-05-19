// =====================================================
// CraterMarchRigControlComponent.cpp
// Purpose: Implements dynamic bone control using Control Rig.
// This will later be expanded for spine bending, tail control, etc.
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

    ControlRigComp = NewObject<UControlRigComponent>(this);
    ControlRigComp->RegisterComponent();
    ControlRigComp->AttachToComponent(GetOwner()->GetRootComponent(), 
        FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void UCraterMarchRigControlComponent::UpdateRigControls(float NeckTurnValue, bool bHighPosture)
{
    if (!ControlRigComp) return;

    // Neck Control
    FTransform NeckTransform;
    NeckTransform.SetRotation(FRotator(0.0f, NeckTurnValue * 45.0f, 0.0f).Quaternion());
    ControlRigComp->SetControlTransform(FName("NeckControl"), NeckTransform);

    // High Posture (raised head)
    if (bHighPosture)
    {
        FTransform HighTransform;
        HighTransform.SetRotation(FRotator(-35.0f, NeckTurnValue * 30.0f, 0.0f).Quaternion());
        ControlRigComp->SetControlTransform(FName("HeadControl"), HighTransform);
    }
}
