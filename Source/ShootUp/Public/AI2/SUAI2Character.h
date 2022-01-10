#pragma once

#include "CoreMinimal.h"
#include "Player/SUBaseCharacter.h"
#include "SUAI2Character.generated.h"

class UBehaviorTree;


UCLASS()
class SHOOTUP_API ASUAI2Character : public ASUBaseCharacter
{
    GENERATED_BODY()

public:
    ASUAI2Character(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:

    virtual void OnDeath() override;
};
