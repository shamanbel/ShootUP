// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Pickups/SUBasePickUP.h"
#include "SUHealthPickUP.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTUP_API ASUHealthPickUP : public ASUBasePickUP
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
   float HealthAmount = 50;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn)override;
	 
};
