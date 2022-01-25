// The numbers lead a dance

#include "Weapon/SUUziWeapon.h"
#include "Engine/World.h"
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

    //���������� � ��������� ���� �������
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)  // bBlockingHit - ��� ��������� true
    {
    MakeDamage(HitResult);
    //������� ������������ ����� ��������� ��e���
    WeaponFXComponent->PlayImpactFX(HitResult);
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
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    
}

bool ASUUziWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    //������� � ��������� ��������� �� ������
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

//������� ���� ��� Actor
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

