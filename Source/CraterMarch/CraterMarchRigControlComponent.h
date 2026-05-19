// =====================================================
// CraterMarchRigControlComponent.h
// Purpose: Controls bone animation via Control Rig.
// Currently handles neck, but designed to be expanded to spine, tail, and different attack types.
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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Control Rig")
    UControlRigComponent* ControlRigComp;

    // Main update function - called every frame from character
    UFUNCTION(BlueprintCallable, Category = "Rig Control")
    void UpdateRigControls(float NeckTurnValue, bool bHighPosture);

protected:
    virtual void BeginPlay() override;
};
