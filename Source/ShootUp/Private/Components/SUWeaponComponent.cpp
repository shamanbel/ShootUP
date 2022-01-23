// The numbers lead a dance


#include "Components/SUWeaponComponent.h"
#include "Weapon/SUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/SUEquipFinishedAnimNotify.h"



USUWeaponComponent::USUWeaponComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

}

void USUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentWeaponIndex = 0;//Выбирает первое оружие - пистолет
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

// Уничтожение массива оружия
  void USUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)

    {
      CurrentWeapon = nullptr;
        for (auto Weapon : Weapons)
      {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
      }
      Weapons.Empty();
      Super::EndPlay(EndPlayReason);
    };

void USUWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ASUBaseWeapon>(WeaponClass);
        if (!Weapon) continue;
        Weapon->OnClipEmpty.AddUObject(this, &USUWeaponComponent::OnEmptyClip);

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

       AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
 }

void USUWeaponComponent::AttachWeaponToSocket(ASUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) 
{
    if (!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USUWeaponComponent::EquipWeapon(int32 WeaponIndex) 
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->Zoom(false);
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);//Прикрепляем на ногу
 }
        CurrentWeapon = Weapons[WeaponIndex];
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);//Прикрепляем к руке
        EquipAnimInProgress = true;
        PlayAnimMontage(EquipAnimMontage);
}

//Постоянная Стрельба при нажатой ЛКМ

void USUWeaponComponent::StartFire()
{
   if (!CanFire()) return;

    CurrentWeapon->StartFire();
}

void USUWeaponComponent::StartFireAI() 
{
    
   CurrentWeapon->StartFireAI();
}

void USUWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;

    CurrentWeapon->StopFire();
}

void USUWeaponComponent::NextWeapon() 
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USUWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)

{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    Character->PlayAnimMontage(Animation);
}
void USUWeaponComponent::InitAnimations()

    {
    if (!EquipAnimMontage) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent: NotifyEvents)

    {
        auto EquipFinishedNotify = Cast<USUEquipFinishedAnimNotify>(NotifyEvent.Notify);
        if (EquipFinishedNotify)
        {
            EquipFinishedNotify->OnNotified.AddUObject(this, &USUWeaponComponent::OnEquipFinished);
            break;
        }
    }
};
void USUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh()) return;
 
        EquipAnimInProgress = false;
   
    
}
void USUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh()) return;

    ReloadAnimInProgress = false;
}

bool USUWeaponComponent::CanFire() const 
{
    return CurrentWeapon && !EquipAnimInProgress;
    //
};
bool USUWeaponComponent::CanEquip() const 
{
    return !EquipAnimInProgress;
}

bool USUWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimMontage && !ReloadAnimMontage && CurrentWeapon->CanReload();
}

void USUWeaponComponent::Reload()
{
     ChangeClip();
}
void USUWeaponComponent::OnEmptyClip(ASUBaseWeapon * AmmoEmptyWeapon)
{   
    if (!AmmoEmptyWeapon) return;

    if(CurrentWeapon == AmmoEmptyWeapon) 
    {
        ChangeClip();
    }
    else
    {
        for (const auto Weapon: Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
    
};
void USUWeaponComponent::ChangeClip()
{
  
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
   
    ReloadAnimInProgress = true;
    PlayAnimMontage(ReloadAnimMontage);
};
bool USUWeaponComponent::GetWeaponUIData(FWeaponUIData& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool USUWeaponComponent::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}

bool USUWeaponComponent::TryToAddAmmo(TSubclassOf<ASUBaseWeapon> WeaponType, int32 ClipsAmount) 
{
    for (const auto Weapon:Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);

        }
    }
    return false;
}

void USUWeaponComponent::Zoom(bool Enabled) 
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Zoom(Enabled);
    }
}
