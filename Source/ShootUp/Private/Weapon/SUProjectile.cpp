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

    //����� ��� ����
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(1.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//�������� ������ �� ���������
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
   // CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true); ������������ ���� � ������ ���������
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASUProjectile::OnProjectileHit);//������� ������������ � �������
   
    //������� ��������� ����
    SetLifeSpan(LifeProjectile);
}

void ASUProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;
    MovementComponent->StopMovementImmediately();

    //������� ����
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