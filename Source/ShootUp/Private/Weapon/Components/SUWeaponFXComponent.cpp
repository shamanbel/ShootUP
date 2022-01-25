 // The numbers lead a dance


#include "Weapon/Components/SUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USUWeaponFXComponent::USUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void USUWeaponFXComponent::USUWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) 
{
    auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
	}

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}





