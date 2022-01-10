// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUDevDamageActor.generated.h"

UCLASS()
class SHOOTUP_API ASUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASUDevDamageActor();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
    USceneComponent* SceneComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    float Radius = 300.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Orange;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    float Damage = 5.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;



protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

};
