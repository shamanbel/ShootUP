// The numbers lead a dance

#include "Weapon/SUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/SUWeaponFXComponent.h"

ASUProjectile::ASUProjectile()
{

    PrimaryActorTick.bCanEverTick = false;

    //Сфера для пули
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(1.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//Коллизия только на попадание
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 3000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

     WeaponFXComponent = CreateDefaultSubobject<USUWeaponFXComponent>("WeaponFXComponent");
}

void ASUProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
   // CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true); столкновение пули и своего персонажа
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASUProjectile::OnProjectileHit);//Делегат Столкновение с актором
   
    //Удаляем улетевшие пули
    SetLifeSpan(LifeProjectile);
}

void ASUProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;
    MovementComponent->StopMovementImmediately();

    //нанести урон
    UGameplayStatics:: ApplyRadialDamage 
    (
        GetWorld(),                       //
        DamageAmount,                     //
        GetActorLocation(),               //
        DamageRadius,                     //
        UDamageType::StaticClass(),       //
        {GetOwner()},                     //
        this,                             //
        GetController(),                    //
        true
    );

     DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 8.0f);

     WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* ASUProjectile::GetController() const 
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}