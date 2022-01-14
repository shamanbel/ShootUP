// The numbers lead a dance


#include "Components/SUHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SUGameModeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"



DEFINE_LOG_CATEGORY_STATIC(LogHealth,All,All)

USUHealthComponent::USUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USUHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(USUHealthComponent, Health);
}

void USUHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    check(MaxHealth > 0);
	Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();

	if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USUHealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USUHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USUHealthComponent::OnTakeRadialDamage);
	}

}


void USUHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
   
}

void USUHealthComponent::Killed(AController* KillerController) 
{
    if (!GetWorld()) return;
    const auto GameMode = Cast<ASUGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;
    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);
    
}

bool USUHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;

    SetHealth(Health + HealthAmount);
    return true;
}

bool USUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

 void USUHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy) 
 {
     if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;
     UAISense_Damage::ReportDamageEvent(
         GetWorld(),                                    //
         GetOwner(),                                    //
         InstigatedBy->GetPawn(),                       //
         Damage,                                        //
         InstigatedBy->GetPawn()->GetActorLocation(),   //
         GetOwner()->GetActorLocation());
 }

 void USUHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
     UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
 {
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
     //UE_LOG(LogHealth, Display, TEXT("OnPOINTDamage: %f, final damage :%f, bone: %s"), Damage, FinalDamage, * BoneName.ToString());
     ApplyDamage(FinalDamage, InstigatedBy);
 }

 void USUHealthComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
     FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
 {
     UE_LOG(LogHealth, Display, TEXT("OnRADIALDamage: %f"), Damage);
     ApplyDamage(Damage, InstigatedBy);
 }
 void USUHealthComponent::OnTakeAnyDamage(
     AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
 {
    ApplyDamage(Damage, InstigatedBy);
 }

 void USUHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy) 
 {
     if (Damage <= 0.0f || IsDead()) return;

     Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
     OnHealthChanged.Broadcast(Health);

     if (IsDead())
     {
         Killed(InstigatedBy);
         OnDeath.Broadcast();
     }
     ReportDamageEvent(Damage, InstigatedBy);
 }

 float USUHealthComponent::GetPointDamageModifier(AActor* DamageActor, const FName& BoneName)
 {
     const auto Character = Cast<ACharacter> (DamageActor);
     if (!Character ||                                         //
         !Character->GetMesh() ||                              //
         !Character->GetMesh()->GetBodyInstance(BoneName))     //
         return 1.0f;

     const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
     if (!PhysMaterial  || !DamageModifiers.Contains(PhysMaterial)) return 1.0f;

     return DamageModifiers[PhysMaterial];


 }