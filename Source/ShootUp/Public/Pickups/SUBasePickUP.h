// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUBasePickUP.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTUP_API ASUBasePickUP : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ASUBasePickUP();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    USoundCue* PickupTakenSound;

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	float RotationYaw = 0.0f;
	virtual bool GivePickupTo(APawn* PlayerPawn);
    UFUNCTION(NetMulticast, Reliable)
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
