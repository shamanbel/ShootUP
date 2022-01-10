// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Components/SUWeaponComponent.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/SUBaseWeapon.h"
#include "SUPlayerHUDWidget.generated.h"

class USUHealthComponent;

UCLASS()
class SHOOTUP_API USUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

     UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

private:
    USUHealthComponent* GetHealthComponent() const;
};
