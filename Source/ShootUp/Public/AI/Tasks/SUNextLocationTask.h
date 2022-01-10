// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SUNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTUP_API USUNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
    USUNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") 
		float Radius = 1000.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
     FBlackboardKeySelector AimLocationKey; //Ранд Точка для передвижения NPC  
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
     bool SelfCenter = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"));
    FBlackboardKeySelector CenterActorKey;

};
