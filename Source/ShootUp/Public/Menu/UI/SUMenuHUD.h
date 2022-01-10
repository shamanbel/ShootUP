// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SUMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTUP_API ASUMenuHUD : public AHUD
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

	virtual void BeginPlay() override;

};
