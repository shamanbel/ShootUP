// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SUCoreTypes.h"
#include "SUGameHUD.generated.h"


UCLASS()
class SHOOTUP_API ASUGameHUD : public AHUD
{
	GENERATED_BODY()
public:
    virtual void DrawHUD() override;

protected:

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
 TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
 TSubclassOf<UUserWidget> PauseWidgetClass;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
 TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<ESUMatchState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurrentWidget = nullptr;


    void DrawCross();
    void OnMatchStateChanged(ESUMatchState State); 

};
