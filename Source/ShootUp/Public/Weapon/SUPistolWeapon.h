// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SUBaseWeapon.h"
#include "SUPistolWeapon.generated.h"

class ASUProjectile;
class USoundCue;
class UAudioComponent;




UCLASS()
class SHOOTUP_API ASUPistolWeapon : public ASUBaseWeapon
{
	GENERATED_BODY()

public:
    //UFUNCTION(Server, Reliable)
    virtual void StartFire() override;
    virtual void StartFireAI() override;
    virtual void Zoom(bool Enabled) override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASUProjectile> ProjestileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoomAngle = 50.0f;

    UPROPERTY()
    UAudioComponent* FireAudioComponent;

 /*   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* NoAmmoSound;*/

  //UFUNCTION(Server, Reliable)
   virtual void MakeShot() override;

   void MakeDamage(const FHitResult& HitResult);

   private:
   AController* GetController() const;

   float DefaultCameraFOV = 90.0f;
};
