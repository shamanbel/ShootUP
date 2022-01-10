 //The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Player/SUBaseCharacter.h"
#include "SUAICharacter.generated.h"


class UBehaviorTree;


UCLASS()
class SHOOTUP_API ASUAICharacter : public ASUBaseCharacter
{
    GENERATED_BODY()

public:
    ASUAICharacter(const FObjectInitializer& ObjInit);

   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:

  
    virtual void OnDeath() override;
};
