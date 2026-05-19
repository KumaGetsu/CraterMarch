// CraterMarchGameMode.cpp
#include "CraterMarchGameMode.h"
#include "CraterMarchCharacter.h"

ACraterMarchGameMode::ACraterMarchGameMode()
{
    DefaultPawnClass = ACraterMarchCharacter::StaticClass();
}
