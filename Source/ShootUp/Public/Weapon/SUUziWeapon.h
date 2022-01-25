// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SUBaseWeapon.h"
#include "SUUziWeapon.generated.h"

class USUWeaponFXComponent;
class UAudioComponent;

UCLASS()
class SHOOTUP_API ASUUziWeapon : public ASUBaseWeapon
{
	GENERATED_BODY()
public:

    ASUUziWeapon();

    virtual void StartFire()override;
    virtual void StopFire() override;

    

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.2f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 2.0f;//Разброс

   /* UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.0f;*/

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    USUWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;


private:
    FTimerHandle ShotTimerHandle;
    UPROPERTY()
    UAudioComponent* FireAudioComponent;


    void MakeDamage(const FHitResult& HitResult);

    AController* GetController() const;
};
