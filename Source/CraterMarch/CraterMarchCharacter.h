// =====================================================
// CraterMarchCharacter.h
// Purpose: Main dinosaur class for the Phase Zero Prototype.
// Owns all components and serves as the root for combat and survival systems.
// =====================================================

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CraterMarchCharacter.generated.h"

class UCraterMarchCombatComponent;
class UCraterMarchModifierComponent;
class UCraterMarchRigControlComponent;
class UPhysicsHandleComponent;

UCLASS()
class CRATERMARCH_API ACraterMarchCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ACraterMarchCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCraterMarchCombatComponent* CombatComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCraterMarchModifierComponent* ModifierComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCraterMarchRigControlComponent* RigControlComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UPhysicsHandleComponent* PhysicsHandle;

    // Survival Stats
    UPROPERTY(ReplicatedUsing = OnRep_Health)
    float Health = 100.0f;

    UPROPERTY(ReplicatedUsing = OnRep_Stamina)
    float Stamina = 100.0f;

    UPROPERTY(Replicated)
    float Food = 100.0f;

    UPROPERTY(Replicated)
    float Water = 100.0f;

    UPROPERTY(Replicated)
    bool bIsBeingGrabbed = false;

    UPROPERTY(Replicated)
    ACraterMarchCharacter* GrabbedBy = nullptr;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION() void OnRep_Health();
    UFUNCTION() void OnRep_Stamina();

    // Input
    UFUNCTION(BlueprintCallable) void OnLeftModifierPressed();
    UFUNCTION(BlueprintCallable) void OnLeftModifierReleased();
    UFUNCTION(BlueprintCallable) void OnRightModifierPressed();
    UFUNCTION(BlueprintCallable) void OnRightModifierReleased();
    UFUNCTION(BlueprintCallable) void OnPrimaryAttackPressed();
    UFUNCTION(BlueprintCallable) void OnPrimaryAttackReleased();

    // Grab
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_AttemptGrab(ACraterMarchCharacter* Target);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_OnGrabbed(ACraterMarchCharacter* Attacker);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_OnGrabReleased();
};    UPhysicsHandleComponent* PhysicsHandle;

    // Survival Stats
    UPROPERTY(ReplicatedUsing = OnRep_Health)
    float Health = 100.0f;

    UPROPERTY(ReplicatedUsing = OnRep_Stamina)
    float Stamina = 100.0f;

    UPROPERTY(Replicated)
    float Food = 100.0f;

    UPROPERTY(Replicated)
    float Water = 100.0f;

    // Grab State
    UPROPERTY(Replicated)
    bool bIsBeingGrabbed = false;

    UPROPERTY(Replicated)
    ACraterMarchCharacter* GrabbedBy = nullptr;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION() void OnRep_Health();
    UFUNCTION() void OnRep_Stamina();

    // Input Functions
    UFUNCTION(BlueprintCallable) void OnLeftModifierPressed();
    UFUNCTION(BlueprintCallable) void OnLeftModifierReleased();
    UFUNCTION(BlueprintCallable) void OnRightModifierPressed();
    UFUNCTION(BlueprintCallable) void OnRightModifierReleased();
    UFUNCTION(BlueprintCallable) void OnPrimaryAttackPressed();
    UFUNCTION(BlueprintCallable) void OnPrimaryAttackReleased();

    // Grab Functions
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_AttemptGrab(ACraterMarchCharacter* Target);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_OnGrabbed(ACraterMarchCharacter* Attacker);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_OnGrabReleased();
};
