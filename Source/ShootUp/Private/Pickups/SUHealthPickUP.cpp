// The numbers lead a dance


#include "Pickups/SUHealthPickUP.h"
#include "Components/SUHealthComponent.h"
#include "SUUtils.h"


bool ASUHealthPickUP::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = SUUtils::GetSUPlayerComponent<USUHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
    ;
}