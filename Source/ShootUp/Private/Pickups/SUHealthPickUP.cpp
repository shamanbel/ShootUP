// The numbers lead a dance


#include "Pickups/SUHealthPickUP.h"
#include "Components/SUHealthComponent.h"
#include "SUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);

bool ASUHealthPickUP::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = SUUtils::GetSUPlayerComponent<USUHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;

    //UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
    return HealthComponent->TryToAddHealth(HealthAmount);
    ;
}