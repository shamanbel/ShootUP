// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SUGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTUP_API USUGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
    FName GetStartupLevelName() const { return StartupLevelName; }
    FName GetMenuLevelName() const { return MenuLevelName; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;
	
};
