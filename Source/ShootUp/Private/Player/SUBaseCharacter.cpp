// The numbers lead a dance


#include "Player/SUBaseCharacter.h"
#include "Components/SUCharacterMovementComponent.h"
#include "Components/SUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SUWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon/SUBaseWeapon.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharterLog, All, All);

ASUBaseCharacter::ASUBaseCharacter(const FObjectInitializer& ObjInit)
   : Super(ObjInit.SetDefaultSubobjectClass<USUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    HealthComponent = CreateDefaultSubobject<USUHealthComponent>("HealthComponent");
    //HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    //HealthTextComponent->SetupAttachment(GetRootComponent());
    WeaponComponent = CreateDefaultSubobject<USUWeaponComponent>("WeaponComponent");
}

void ASUBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    check(HealthComponent);
    check(GetCharacterMovement());
    
    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASUBaseCharacter::OnHealthChanged);
    
}

void ASUBaseCharacter::OnHealthChanged(float Health)
{
   
}

void ASUBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



bool ASUBaseCharacter::IsRunning() const
{
    return false;
}

void ASUBaseCharacter::OnDeath() 
{
    UE_LOG(BaseCharterLog, Warning, TEXT("Player %s IS DEAD"), *GetName());
    //PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    //Игнор капсулы коллизии убитого актора
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ASUBaseCharacter::TurnOff()
{
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    Super::TurnOff();

}

void ASUBaseCharacter::Reset() 
{
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    Super::Reset();
}
//void ASUBaseCharacter::SpawnWeapon()
//{
//    //if (!GetWorld()) return;
//    const auto Weapon = GetWorld()->SpawnActor<ASUBaseWeapon>(WeaponClass);
//    if (Weapon)
//    {
//        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
//        Weapon->AttachToComponent(GetMesh(), AttachmentRules, "WeaponSocket");
//    }
//}



