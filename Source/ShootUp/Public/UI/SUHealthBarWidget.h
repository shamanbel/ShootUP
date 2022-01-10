// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SUHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTUP_API USUHealthBarWidget : public UUserWidget
{
	GENERATED_BODY() 

public:

    void SetHealthPercent(float Percent);

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisibilityThreshold = 0.8;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::Green;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;
};
