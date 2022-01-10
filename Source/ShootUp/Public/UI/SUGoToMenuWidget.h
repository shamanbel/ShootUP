// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUGoToMenuWidget.generated.h"

class UButton;
UCLASS()
class SHOOTUP_API USUGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY ( meta = (BindWidget) )
	UButton* GoToMenuButton;

	virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnGoToMenu();
	
};
