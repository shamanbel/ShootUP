// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTUP_API USUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);


protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;



};
