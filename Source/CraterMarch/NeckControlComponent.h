// =====================================================
// NeckControlComponent.h
// Purpose: This component uses Control Rig to dynamically rotate the dinosaur's neck and head in real time.
// It receives data from the ModifierComponent and translates it into visible bone transformations.
// This is a key part of making the modifier combat feel responsive and physical.
// =====================================================

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NeckControlComponent.generated.h"

class UControlRigComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRATERMARCH_API UNeckControlComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNeckControlComponent();

    // The Control Rig component that actually moves the bones
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control Rig")
    UControlRigComponent* ControlRigComp;

    // Main function called every frame from the character
    UFUNCTION(BlueprintCallable, Category = "Neck Control")
    void UpdateNeckRotation(float TurnValue, bool bHighPosture);

protected:
    virtual void BeginPlay() override;
};
