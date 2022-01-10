 //The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SUWeaponFXComponent.generated.h"

class UNiagaraSystem;
 class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTUP_API USUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USUWeaponFXComponent();

	void PlayImpactFX(const FHitResult& Hit);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* DefaultEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;


public:	

};
