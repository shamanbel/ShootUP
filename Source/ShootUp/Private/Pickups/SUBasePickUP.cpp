// The numbers lead a dance


#include "Pickups/SUBasePickUP.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

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
    UE_LOG(LogBasePickup, Display, TEXT("Pickup go on"));

}

bool ASUBasePickUP::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASUBasePickUP::PickupWasTaken()

{
	//Игнор коллизии pickup
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    // Делаем невидимым

	GetRootComponent()->SetVisibility(false, true);
    FTimerHandle RespawnTimeHandle;
    GetWorldTimerManager().SetTimer(RespawnTimeHandle, this, &ASUBasePickUP::Respawn, RespawnTime);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
};
void ASUBasePickUP::Respawn()
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