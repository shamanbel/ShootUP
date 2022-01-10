// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SUFireService.generated.h"


UCLASS()
class SHOOTUP_API USUFireService : public UBTService
{
    GENERATED_BODY()

public:
    USUFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
