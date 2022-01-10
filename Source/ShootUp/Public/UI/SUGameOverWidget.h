// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUCoreTypes.h"
#include "SUGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTUP_API USUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(ESUMatchState State);
    void UpdatePlayerState();

    UFUNCTION()
    void OnResetLevel();

	
};
