// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUMenuWidget.generated.h"

class UButton;
class USoundCue;   

UCLASS()
class SHOOTUP_API USUMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;


    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;


private:
    UFUNCTION()
    void ONStartGame();

     UFUNCTION()
    void ONQuitGame();

};
