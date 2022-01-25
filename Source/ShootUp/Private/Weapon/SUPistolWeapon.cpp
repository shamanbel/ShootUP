// The numbers lead a dance


#include "Weapon/SUPistolWeapon.h"
#include "Weapon/SUProjectile.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"


void ASUPistolWeapon::StartFire()
{
    MakeShot();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
void ASUPistolWeapon::StartFireAI()
{
    MakeShot();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
//спаун пули
//void ASUPistolWeapon::MakeShot_Implementation()
void ASUPistolWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) return;
    FVector TraceStart;
    FVector TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    
    ASUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASUProjectile>( ProjestileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    //установить параметры для Projectile

    

}


AController* ASUPistolWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void ASUPistolWeapon::Zoom(bool Enabled)
{
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller || !Controller->PlayerCameraManager) return;

    if (Enabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }

   Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}