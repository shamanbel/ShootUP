// The numbers lead a dance


#include "AI/Services/SUFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Components/SUWeaponComponent.h"
#include "SUUtils.h"


USUFireService::USUFireService() 
{
    NodeName = "Fire";
}


void USUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
   const auto Blackboard = OwnerComp.GetBlackboardComponent();

   const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (const auto Controller = OwnerComp.GetAIOwner())
    {
        if (const auto WeaponComponent = SUUtils::GetSUPlayerComponent<USUWeaponComponent>(Controller->GetPawn()))
        {
            HasAim ? WeaponComponent->StartFireAI() : WeaponComponent->StopFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

};

