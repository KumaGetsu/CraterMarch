// CraterMarchModifierComponent.h
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CraterMarchModifierComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRATERMARCH_API UCraterMarchModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCraterMarchModifierComponent();

	UPROPERTY(Replicated)
	bool bLeftModifierPressed = false;

	UPROPERTY(Replicated)
	bool bRightModifierPressed = false;

	UPROPERTY(Replicated)
	float NeckTurnValue = 0.0f;

	UPROPERTY(Replicated)
	bool bIsHighPosture = false;

	UFUNCTION(BlueprintCallable, Category = "Modifier")
	float GetNeckTurnValue() const { return NeckTurnValue; }

	UFUNCTION(BlueprintCallable, Category = "Modifier")
	bool IsHighPosture() const { return bIsHighPosture; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UpdateModifierState(bool bLeft, bool bRight);
};