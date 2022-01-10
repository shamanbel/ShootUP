// The numbers lead a dance


#include "Pickups/SUAmmoPickUP.h"
#include "Components/SUHealthComponent.h"
#include "Components/SUWeaponComponent.h"
#include "SUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool ASUAmmoPickUP::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = SUUtils::GetSUPlayerComponent<USUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;//Смерть песрсонажа
     
    const auto WeaponComponent = SUUtils::GetSUPlayerComponent<USUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

    UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
