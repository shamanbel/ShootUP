// The numbers lead a dance


#include "UI/SUPlayerHUDWidget.h"
#include "Components/SUHealthComponent.h"
#include "Components/SUWeaponComponent.h"


float USUPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;
    const auto Component = Player->GetComponentByClass(USUHealthComponent::StaticClass());
    const auto HealthComponent = Cast<USUHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;
    return HealthComponent->GetHealthPercent();
}

bool USUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto Component = Player->GetComponentByClass(USUWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<USUWeaponComponent>(Component);
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(UIData);
}

bool USUPlayerHUDWidget:: IsPlayerAlive() const 
{
    const auto HealthComponent = GetHealthComponent();
    return HealthComponent && !HealthComponent->IsDead();
}
bool USUPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto Component = Player->GetComponentByClass(USUWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<USUWeaponComponent>(Component);
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

USUHealthComponent* USUPlayerHUDWidget::GetHealthComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    const auto Component = Player->GetComponentByClass(USUHealthComponent::StaticClass());
    const auto HealthComponent = Cast<USUHealthComponent>(Component);
    return HealthComponent;
}