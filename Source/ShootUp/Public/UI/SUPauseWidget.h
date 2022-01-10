// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUPauseWidget.generated.h"

class UButton;
class USoundCue;

    UCLASS()
class SHOOTUP_API USUPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* OpenSound;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
};
