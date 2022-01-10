// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTUP_API USUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    virtual float GetMaxSpeed() const override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin ="1.5", ClampMax = "10.0"))
    float RunModifier = 2.0f;
};
