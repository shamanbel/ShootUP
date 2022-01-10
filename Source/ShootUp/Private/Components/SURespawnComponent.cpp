// The numbers lead a dance


#include "Components/SURespawnComponent.h"
#include  "SUGameModeBase.h"


USURespawnComponent::USURespawnComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	
}

void USURespawnComponent::USURespawnComponent::Respawn(int32 RespawnTime) 
{
    if (!GetWorld())  return;

		RespawnCoutDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USURespawnComponent::RespawnTimeUpdate, 1.0f, true);

}

void USURespawnComponent::USURespawnComponent::RespawnTimeUpdate() 
{
    if (--RespawnCoutDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<ASUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
