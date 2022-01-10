// The numbers lead a dance

#include "AI/Services/SUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "SUUtils.h"
#include "Components/SUAIPerceptionComponent.h"

USUFindEnemyService::USUFindEnemyService() 
{
    NodeName = "Find Enemy";
}

void USUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = SUUtils::GetSUPlayerComponent<USUAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}