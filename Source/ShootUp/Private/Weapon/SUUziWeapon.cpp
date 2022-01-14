// The numbers lead a dance

#include "Weapon/SUUziWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/SUWeaponFXComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


ASUUziWeapon::ASUUziWeapon() 
{
    WeaponFXComponent = CreateDefaultSubobject<USUWeaponFXComponent>("WeaponFXComponent");

}

void ASUUziWeapon::BeginPlay() 
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

DEFINE_LOG_CATEGORY_STATIC(LogUziWeapon, All, All);

float DamageAmount = 10.0f;

void ASUUziWeapon::MakeShot()
{
   
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
       
        return;
    }
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) 
    {
        StopFire();
        return;
    };

    //Информация о поражении цели трайсом
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)  // bBlockingHit - при попадании true
    {
        MakeDamage(HitResult);

        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);

        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        //Выводит наименование кости попадания трaйса
        WeaponFXComponent->PlayImpactFX(HitResult);

        UE_LOG(LogUziWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
  
    
    DecreaseAmmo();
}

void ASUUziWeapon::StartFire()
{
    MakeShot();
    FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    FireAudioComponent->Play();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASUUziWeapon::MakeShot, TimeBetweenShots, true);
}
void ASUUziWeapon::StopFire()
{
    if (FireAudioComponent)
    {
        FireAudioComponent->Stop();
    }
    
    //UE_LOG(LogBaseWeapon, Display, TEXT("StopFIRE"));
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    
}

bool ASUUziWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    //выстрел с разбросом попаданий по конусу
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

//Наносим урон для Actor
void ASUUziWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;
    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;

    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}
AController* ASUUziWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

