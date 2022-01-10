// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SUFindEnemyService.generated.h"


UCLASS()
class SHOOTUP_API USUFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
    USUFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    //Поиск противника
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
