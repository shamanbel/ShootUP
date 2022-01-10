// The numbers lead a dance


#include "AI/SUAIController.h"
#include "AI/SUAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SUAIPerceptionComponent.h"
#include "Components/SURespawnComponent.h"

ASUAIController::ASUAIController() 
{
    SUAIPerceptionComponent = CreateDefaultSubobject<USUAIPerceptionComponent>("SUAIPerceptionComponent");
        SetPerceptionComponent(*SUAIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<USURespawnComponent>("RespawnComponent");
    
    bWantsPlayerState = true;
}
void ASUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto SUCharacter = Cast<ASUAICharacter>(InPawn))
    {
        RunBehaviorTree(SUCharacter->BehaviorTreeAsset);
    }
}
void ASUAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASUAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}