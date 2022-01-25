// The numbers lead a dance


#include "Pickups/SUBasePickUP.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"


ASUBasePickUP::ASUBasePickUP()
{
 
	PrimaryActorTick.bCanEverTick = true;
	//создание объекта Pickup
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);  //Коллизия только на попадание
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);

}


void ASUBasePickUP::BeginPlay()
{
	Super::BeginPlay();
    check(CollisionComponent);
    GenerateRotationYaw();
}


void ASUBasePickUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

}

void ASUBasePickUP::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

bool ASUBasePickUP::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASUBasePickUP::PickupWasTaken_Implementation()

{
	//Игнор коллизии pickup
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    // Делаем невидимым

	GetRootComponent()->SetVisibility(false, true);
    FTimerHandle RespawnTimeHandle;
    GetWorldTimerManager().SetTimer(RespawnTimeHandle, this, &ASUBasePickUP::Respawn, RespawnTime);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
};
void ASUBasePickUP::Respawn_Implementation()
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

void ASUBasePickUP::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;

    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
};