// =====================================================
// CraterMarchCombatComponent.h
// Purpose: Core combat logic for the prototype.
// Handles charging attacks, hit detection, and initiates the grab system.
// All critical combat decisions are server-authoritative.
// =====================================================

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CraterMarchCombatComponent.generated.h"

class ACraterMarchCharacter;

UENUM(BlueprintType)
enum class ECombatState : uint8
{
    Idle			UMETA(DisplayName = "Idle"),
    Charging		UMETA(DisplayName = "Charging"),
    Grabbing		UMETA(DisplayName = "Grabbing")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRATERMARCH_API UCraterMarchCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCraterMarchCombatComponent();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    ECombatState CurrentCombatState = ECombatState::Idle;

    // Combat Configuration
    UPROPERTY(EditAnywhere, Category = "Combat|Charge")
    float MaxChargeTime = 1.8f;

    UPROPERTY(EditAnywhere, Category = "Combat|Damage")
    float BaseBiteDamage = 22.0f;

    UPROPERTY(EditAnywhere, Category = "Combat|Stamina")
    float ChargeStaminaCostPerSecond = 12.0f;

    // Called from character input
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StartChargingAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ReleaseAttack();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_ReleaseAttack();

protected:
    float CurrentChargeTime = 0.0f;
    bool bIsCharging = false;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    float CalculateDamage(float ChargeRatio) const;
};
    UPROPERTY(EditAnywhere, Category = "Combat|Damage")
    float BaseBiteDamage = 22.0f;

    UPROPERTY(EditAnywhere, Category = "Combat|Stamina")
    float ChargeStaminaCostPerSecond = 12.0f;

    // Called from character input
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StartChargingAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ReleaseAttack();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_ReleaseAttack();

protected:
    float CurrentChargeTime = 0.0f;
    bool bIsCharging = false;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    float CalculateDamage(float ChargeRatio) const;
};
