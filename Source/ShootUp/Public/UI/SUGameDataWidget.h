// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUGameDataWidget.generated.h"

class ASUGameModeBase;
class ASUPlayerState;

UCLASS()
class SHOOTUP_API USUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundsNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondsRemaining() const;

private:
    ASUGameModeBase* GetSUGameMode() const;
    ASUPlayerState* GetSUPlayerState() const;
	
};
