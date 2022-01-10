// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTUP_API USURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USURespawnComponent();

	void Respawn(int32 RespawnTime);

protected:
private:
    FTimerHandle RespawnTimerHandle;
	int32 RespawnCoutDown = 0;

	void RespawnTimeUpdate();
	


};
