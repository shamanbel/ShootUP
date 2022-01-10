// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class USUWeaponFXComponent;

UCLASS()
class SHOOTUP_API ASUProjectile : public AActor
{
    GENERATED_BODY()

public:
    ASUProjectile();

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

     UPROPERTY(VisibleAnywhere, Category = "VFX")
    USUWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 20.0f;  //урон от выстрела пистолета

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeProjectile = 3.0f;  //

    virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

    AController* GetController() const;
    
};