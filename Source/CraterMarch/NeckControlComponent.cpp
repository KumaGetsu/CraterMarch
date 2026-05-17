// =====================================================
// NeckControlComponent.cpp
// Purpose: Implementation of dynamic neck control using Control Rig.
// This makes the modifier inputs visible as real neck movement.
// =====================================================

#include "NeckControlComponent.h"
#include "Components/ControlRigComponent.h"

UNeckControlComponent::UNeckControlComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UNeckControlComponent::BeginPlay()
{
    Super::BeginPlay();

    // Create and register the Control Rig at runtime
    ControlRigComp = NewObject<UControlRigComponent>(this);
    ControlRigComp->RegisterComponent();
    ControlRigComp->AttachToComponent(GetOwner()->GetRootComponent(), 
        FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void UNeckControlComponent::UpdateNeckRotation(float TurnValue, bool bHighPosture)
{
    if (!ControlRigComp) return;

    // Rotate the neck left or right based on modifier input
    FTransform NeckTransform;
    NeckTransform.SetRotation(FRotator(0.0f, TurnValue * 45.0f, 0.0f).Quaternion());
    ControlRigComp->SetControlTransform(FName("NeckControl"), NeckTransform);

    // High Posture raises the head for better attack angle
    if (bHighPosture)
    {
        FTransform HighTransform;
        HighTransform.SetRotation(FRotator(-35.0f, TurnValue * 30.0f, 0.0f).Quaternion());
        ControlRigComp->SetControlTransform(FName("HeadControl"), HighTransform);
    }
}
