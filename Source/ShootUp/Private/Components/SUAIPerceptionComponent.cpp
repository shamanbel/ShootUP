// The numbers lead a dance


#include "Components/SUAIPerceptionComponent.h"
#include "AIController.h"
#include "SUUtils.h"
#include "Components/SUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"



//NPC выбираетближайшего  противника
AActor* USUAIPerceptionComponent::GetClosestEnemy() const 
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if (PercieveActors.Num() == 0) return nullptr;
    }
    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn =nullptr;

    for (const auto PerceiveActor : PercieveActors)
    {
        const auto HealthComponent = SUUtils::GetSUPlayerComponent<USUHealthComponent>(PerceiveActor);
       
        const auto PercievePawn = Cast<APawn>(PerceiveActor);
        const auto AreEnemies = PercievePawn && SUUtils::AreEnemies(Controller, PercievePawn->Controller);

        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
        {
            const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PerceiveActor;
            }
        }
    }
    return BestPawn;
}
