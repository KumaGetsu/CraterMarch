// =====================================================
// CraterMarchCharacter.cpp
// Purpose: Implementation of the main dinosaur character.
// This file handles initialization, tick updates, input binding, replication, and core gameplay logic.
// It connects all the components together.
// =====================================================

#include "CraterMarchCharacter.h"
#include "CraterMarchModifierComponent.h"
#include "CraterMarchRigControlComponent.h"      // Updated name
#include "CraterMarchCombatComponent.h"
#include "Components/PhysicsHandleComponent.h"
#include "EnhancedInputComponent.h"
#include "Net/UnrealNetwork.h"

// =====================================================
// Constructor
// =====================================================
ACraterMarchCharacter::ACraterMarchCharacter()
{
    // Create all components here in C++ for performance and control
    CombatComponent = CreateDefaultSubobject<UCraterMarchCombatComponent>(TEXT("CombatComponent"));
    ModifierComponent = CreateDefaultSubobject<UCraterMarchModifierComponent>(TEXT("ModifierComponent"));
    RigControlComponent = CreateDefaultSubobject<UCraterMarchRigControlComponent>(TEXT("RigControlComponent"));  // Updated name
    
    PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
    
    // Strong physics handle settings for realistic grabs
    PhysicsHandle->LinearDamping = 1200.0f;
    PhysicsHandle->AngularDamping = 1200.0f;
    PhysicsHandle->LinearStiffness = 8000.0f;
    PhysicsHandle->AngularStiffness = 8000.0f;
}

// =====================================================
// BeginPlay & Tick
// =====================================================
void ACraterMarchCharacter::BeginPlay()
{
    Super::BeginPlay();
    SetReplicates(true);
    SetReplicateMovement(true);
}

void ACraterMarchCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update rig controls (neck, future spine/tail) every frame based on modifier input
    if (RigControlComponent && ModifierComponent)
    {
        RigControlComponent->UpdateRigControls(
            ModifierComponent->GetNeckTurnValue(), 
            ModifierComponent->IsHighPosture()
        );
    }

    // Survival & Stamina Logic
    if (CombatComponent)
    {
        if (CombatComponent->CurrentCombatState == ECombatState::Charging)
        {
            Stamina = FMath::Max(0.0f, Stamina - 18.0f * DeltaTime);
        }
    }

    if (bIsBeingGrabbed)
    {
        Stamina = FMath::Max(0.0f, Stamina - 28.0f * DeltaTime);
    }

    // Stamina Regeneration
    if (Stamina < 100.0f && CombatComponent && 
        CombatComponent->CurrentCombatState == ECombatState::Idle && !bIsBeingGrabbed)
    {
        float RegenRate = (Food > 30.0f && Water > 30.0f) ? 15.0f : 7.0f;
        Stamina = FMath::Min(100.0f, Stamina + RegenRate * DeltaTime);
    }

    // Hunger & Thirst
    Food  = FMath::Max(0.0f, Food  - 3.2f * DeltaTime);
    Water = FMath::Max(0.0f, Water - 4.1f * DeltaTime);

    if (Food < 8.0f || Water < 8.0f)
    {
        Health = FMath::Max(0.0f, Health - 7.5f * DeltaTime);
    }
}

// Input Binding
void ACraterMarchCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Modifier Inputs
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_LeftModifier")), 
            ETriggerEvent::Started, this, &ACraterMarchCharacter::OnLeftModifierPressed);
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_LeftModifier")), 
            ETriggerEvent::Completed, this, &ACraterMarchCharacter::OnLeftModifierReleased);

        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_RightModifier")), 
            ETriggerEvent::Started, this, &ACraterMarchCharacter::OnRightModifierPressed);
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_RightModifier")), 
            ETriggerEvent::Completed, this, &ACraterMarchCharacter::OnRightModifierReleased);

        // Attack Input
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_PrimaryAttack")), 
            ETriggerEvent::Started, this, &ACraterMarchCharacter::OnPrimaryAttackPressed);
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_PrimaryAttack")), 
            ETriggerEvent::Completed, this, &ACraterMarchCharacter::OnPrimaryAttackReleased);
    }
}

// Input Handlers
void ACraterMarchCharacter::OnPrimaryAttackPressed()  { if (CombatComponent) CombatComponent->StartChargingAttack(); }
void ACraterMarchCharacter::OnPrimaryAttackReleased() { if (CombatComponent) CombatComponent->ReleaseAttack(); }

void ACraterMarchCharacter::OnLeftModifierPressed()   { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(true, ModifierComponent->bRightModifierPressed); }
void ACraterMarchCharacter::OnLeftModifierReleased()  { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(false, ModifierComponent->bRightModifierPressed); }
void ACraterMarchCharacter::OnRightModifierPressed()  { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(ModifierComponent->bLeftModifierPressed, true); }
void ACraterMarchCharacter::OnRightModifierReleased() { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(ModifierComponent->bLeftModifierPressed, false); }

// Replication
void ACraterMarchCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACraterMarchCharacter, Health);
    DOREPLIFETIME(ACraterMarchCharacter, Stamina);
    DOREPLIFETIME(ACraterMarchCharacter, Food);
    DOREPLIFETIME(ACraterMarchCharacter, Water);
    DOREPLIFETIME(ACraterMarchCharacter, bIsBeingGrabbed);
    DOREPLIFETIME(ACraterMarchCharacter, GrabbedBy);
}// =====================================================
void ACraterMarchCharacter::BeginPlay()
{
    Super::BeginPlay();
    SetReplicates(true);
    SetReplicateMovement(true);
}

void ACraterMarchCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update neck rotation every frame based on modifier input
    if (NeckControlComponent && ModifierComponent)
    {
        NeckControlComponent->UpdateNeckRotation(
            ModifierComponent->GetNeckTurnValue(), 
            ModifierComponent->IsHighPosture()
        );
    }

    // Survival & Stamina Logic
    if (CombatComponent)
    {
        if (CombatComponent->CurrentCombatState == ECombatState::Charging)
        {
            Stamina = FMath::Max(0.0f, Stamina - 18.0f * DeltaTime);
        }
    }

    if (bIsBeingGrabbed)
    {
        Stamina = FMath::Max(0.0f, Stamina - 28.0f * DeltaTime);
    }

    // Stamina Regeneration
    if (Stamina < 100.0f && CombatComponent && 
        CombatComponent->CurrentCombatState == ECombatState::Idle && !bIsBeingGrabbed)
    {
        float RegenRate = (Food > 30.0f && Water > 30.0f) ? 15.0f : 7.0f;
        Stamina = FMath::Min(100.0f, Stamina + RegenRate * DeltaTime);
    }

    // Hunger & Thirst
    Food  = FMath::Max(0.0f, Food  - 3.2f * DeltaTime);
    Water = FMath::Max(0.0f, Water - 4.1f * DeltaTime);

    if (Food < 8.0f || Water < 8.0f)
    {
        Health = FMath::Max(0.0f, Health - 7.5f * DeltaTime);
    }
}

// Input Binding
void ACraterMarchCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Modifier Inputs
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_LeftModifier")), 
            ETriggerEvent::Started, this, &ACraterMarchCharacter::OnLeftModifierPressed);
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_LeftModifier")), 
            ETriggerEvent::Completed, this, &ACraterMarchCharacter::OnLeftModifierReleased);

        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_RightModifier")), 
            ETriggerEvent::Started, this, &ACraterMarchCharacter::OnRightModifierPressed);
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_RightModifier")), 
            ETriggerEvent::Completed, this, &ACraterMarchCharacter::OnRightModifierReleased);

        // Attack Input
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_PrimaryAttack")), 
            ETriggerEvent::Started, this, &ACraterMarchCharacter::OnPrimaryAttackPressed);
        EnhancedInput->BindAction(LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/IA_PrimaryAttack")), 
            ETriggerEvent::Completed, this, &ACraterMarchCharacter::OnPrimaryAttackReleased);
    }
}

// Input Handlers
void ACraterMarchCharacter::OnPrimaryAttackPressed()  { if (CombatComponent) CombatComponent->StartChargingAttack(); }
void ACraterMarchCharacter::OnPrimaryAttackReleased() { if (CombatComponent) CombatComponent->ReleaseAttack(); }

void ACraterMarchCharacter::OnLeftModifierPressed()   { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(true, ModifierComponent->bRightModifierPressed); }
void ACraterMarchCharacter::OnLeftModifierReleased()  { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(false, ModifierComponent->bRightModifierPressed); }
void ACraterMarchCharacter::OnRightModifierPressed()  { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(ModifierComponent->bLeftModifierPressed, true); }
void ACraterMarchCharacter::OnRightModifierReleased() { if (ModifierComponent) ModifierComponent->Server_UpdateModifierState(ModifierComponent->bLeftModifierPressed, false); }

// Replication
void ACraterMarchCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACraterMarchCharacter, Health);
    DOREPLIFETIME(ACraterMarchCharacter, Stamina);
    DOREPLIFETIME(ACraterMarchCharacter, Food);
    DOREPLIFETIME(ACraterMarchCharacter, Water);
    DOREPLIFETIME(ACraterMarchCharacter, bIsBeingGrabbed);
    DOREPLIFETIME(ACraterMarchCharacter, GrabbedBy);
}
