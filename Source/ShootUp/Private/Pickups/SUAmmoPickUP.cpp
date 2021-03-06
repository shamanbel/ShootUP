// The numbers lead a dance


#include "Pickups/SUAmmoPickUP.h"
#include "Components/SUHealthComponent.h"
#include "Components/SUWeaponComponent.h"
#include "SUUtils.h"



bool ASUAmmoPickUP::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = SUUtils::GetSUPlayerComponent<USUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;//?????? ??????????
     
    const auto WeaponComponent = SUUtils::GetSUPlayerComponent<USUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

   return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
