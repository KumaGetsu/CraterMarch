// =====================================================
// CraterMarchCombatComponent.cpp
// Purpose: Implementation of the combat system.
// Handles charging, hit detection (sphere trace from mouth), and initiates grabs.
// All damage and grab logic runs on the server for fairness.
// =====================================================

#include "CraterMarchCombatComponent.h"
#include "CraterMarchCharacter.h"
#include "Net/UnrealNetwork.h"

UCraterMarchCombatComponent::UCraterMarchCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UCraterMarchCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bIsCharging)
    {
        CurrentChargeTime += DeltaTime;

        // Visual feedback for the player
        GEngine->AddOnScreenDebugMessage(1, 0.05f, FColor::Yellow, 
            FString::Printf(TEXT("Charging: %.1f%%"), (CurrentChargeTime / MaxChargeTime) * 100.0f));
    }
}

void UCraterMarchCombatComponent::StartChargingAttack()
{
    if (CurrentCombatState != ECombatState::Idle) return;

    bIsCharging = true;
    CurrentChargeTime = 0.0f;
    CurrentCombatState = ECombatState::Charging;

    GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("Started Charging Attack"));
}

void UCraterMarchCombatComponent::ReleaseAttack()
{
    if (!bIsCharging) return;
    Server_ReleaseAttack();
}

void UCraterMarchCombatComponent::Server_ReleaseAttack_Implementation()
{
    float ChargeRatio = FMath::Clamp(CurrentChargeTime / MaxChargeTime, 0.0f, 1.0f);

    bIsCharging = false;
    CurrentChargeTime = 0.0f;

    ACraterMarchCharacter* OwnerChar = Cast<ACraterMarchCharacter>(GetOwner());
    if (!OwnerChar) return;

    // Sphere trace from mouth position for accurate bite detection
    FVector Start = OwnerChar->GetActorLocation() + OwnerChar->GetActorForwardVector() * 80.0f;
    FVector End = Start + OwnerChar->GetControlRotation().Vector() * 340.0f;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerChar);

    if (GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(45.0f), Params))
    {
        if (ACraterMarchCharacter* Target = Cast<ACraterMarchCharacter>(Hit.GetActor()))
        {
            if (ChargeRatio >= 0.65f) // Strong charge triggers grab
            {
                CurrentCombatState = ECombatState::Grabbing;
                OwnerChar->Server_AttemptGrab(Target);
                return;
            }
        }
    }

    // Quick bite if no grab
    CurrentCombatState = ECombatState::Idle;
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("Quick Bite"));
}

float UCraterMarchCombatComponent::CalculateDamage(float ChargeRatio) const
{
    return BaseBiteDamage * (0.6f + ChargeRatio * 0.8f);
}    CurrentCombatState = ECombatState::Charging;

    GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("Started Charging Attack"));
}

void UCraterMarchCombatComponent::ReleaseAttack()
{
    if (!bIsCharging) return;
    Server_ReleaseAttack();
}

void UCraterMarchCombatComponent::Server_ReleaseAttack_Implementation()
{
    float ChargeRatio = FMath::Clamp(CurrentChargeTime / MaxChargeTime, 0.0f, 1.0f);

    bIsCharging = false;
    CurrentChargeTime = 0.0f;

    ACraterMarchCharacter* OwnerChar = Cast<ACraterMarchCharacter>(GetOwner());
    if (!OwnerChar) return;

    // Sphere trace from mouth for accurate hit detection
    FVector Start = OwnerChar->GetActorLocation() + OwnerChar->GetActorForwardVector() * 80.0f;
    FVector End = Start + OwnerChar->GetControlRotation().Vector() * 340.0f;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerChar);

    if (GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECC_Pawn, FCollisionShape::MakeSphere(45.0f), Params))
    {
        if (ACraterMarchCharacter* Target = Cast<ACraterMarchCharacter>(Hit.GetActor()))
        {
            if (ChargeRatio >= 0.65f)
            {
                CurrentCombatState = ECombatState::Grabbing;
                OwnerChar->Server_AttemptGrab(Target);
                return;
            }
        }
    }

    // Quick bite if no grab
    CurrentCombatState = ECombatState::Idle;
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Orange, TEXT("Quick Bite"));
}

float UCraterMarchCombatComponent::CalculateDamage(float ChargeRatio) const
{
    return BaseBiteDamage * (0.6f + ChargeRatio * 0.8f);
}
