// CraterMarchGameMode.h
// Purpose: Custom GameMode for the prototype. Sets default pawn and handles basic game rules.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CraterMarchGameMode.generated.h"

UCLASS()
class CRATERMARCH_API ACraterMarchGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACraterMarchGameMode();
};
