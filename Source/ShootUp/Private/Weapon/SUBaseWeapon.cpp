// The numbers lead a dance


#include "Weapon/SUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

ASUBaseWeapon::ASUBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
	
}
void ASUBaseWeapon::MakeShot()
{
}
void ASUBaseWeapon::StartFire()
{
    FireInProgress = true;
}
void ASUBaseWeapon::StopFire()
{
    FireInProgress = false;
}

bool ASUBaseWeapon::IsFiring() const
{
    return FireInProgress;
}

void ASUBaseWeapon::StartFireAI()
{
  
}

APlayerController* ASUBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();

   
}
//Прицел для стрельбы
bool ASUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const 
{
    const auto SUCharacter = Cast<ACharacter>(GetOwner());
    if (!SUCharacter) return false;

    if (SUCharacter->IsPlayerControlled())
    {    //Контроль игроком
        const auto Controller = SUCharacter->GetController<APlayerController>();
        if (!Controller) return false;
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
     }
    else
    {    //Контроль AI
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
  return true;
}

FVector ASUBaseWeapon::GetMuzzleWorldLocation() const 
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const 
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

     TraceStart = ViewLocation;

    const FVector ShootDirection =ViewRotation.Vector();
     TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) 
{
 
    if (!GetWorld()) return;

    //Пересечение трэйса с препятствием при выстреле
     FCollisionQueryParams CollisionParams;
    // CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);  // CollisionParams
}

void ASUBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        return;
    }
    CurrentAmmo.Bullets--;
    LogAmmo();
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}
bool ASUBaseWeapon::IsAmmoEmpty() const 
{
    return CurrentAmmo.Clips == 0 && IsClipEmpty();
}
bool ASUBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}
void ASUBaseWeapon::ChangeClip()
{
    if (CurrentAmmo.Clips ==0)
    {
        
        return;
    }
    CurrentAmmo.Clips--;
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(LogBaseWeapon, Display, TEXT("---------RELOAD-------------"));
}
bool ASUBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}
bool ASUBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips &&  //
           CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

//Заполнение магазинов 
 bool ASUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
 {
     if (IsAmmoFull() || ClipsAmount <= 0) return false;
     if (IsAmmoEmpty())
     {
         CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
         OnClipEmpty.Broadcast(this);
     }
     else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
     {
         const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
         if (DefaultAmmo.Clips - NextClipsAmount >= 0)
         {
             CurrentAmmo.Clips = NextClipsAmount;
         }
         else
         {
             CurrentAmmo.Clips = DefaultAmmo.Clips;
             CurrentAmmo.Bullets = DefaultAmmo.Bullets;
         }
     }
     else
     {
         CurrentAmmo.Bullets = DefaultAmmo.Bullets;
     }
     return true;
 }
 
 void ASUBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo:" + FString::FromInt(CurrentAmmo.Bullets) + "/" + FString::FromInt(CurrentAmmo.Clips);
   
}




//    //Наносим урон для Actor
//void ASUBaseWeapon::MakeDamage(const FHitResult& HitResult)
//
//{
//    const auto DamagedActor = HitResult.GetActor();
//    if (!DamagedActor) return;
//
//    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
//}