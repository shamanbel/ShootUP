// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SUBasePickUP.h"
#include "SUAmmoPickUP.generated.h"

class ASUBaseWeapon;

UCLASS()
class SHOOTUP_API ASUAmmoPickUP : public ASUBasePickUP
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASUBaseWeapon> WeaponType;  

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
