// The numbers lead a dance


#include "AI2/SUAI2Controller.h"
#include "AI2/SUAI2Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SUAIPerceptionComponent.h"
#include "Components/SURespawnComponent.h"

   ASUAI2Controller::ASUAI2Controller() 
{
       SUAIPerceptionComponent = CreateDefaultSubobject<USUAIPerceptionComponent>("SUAIPerceptionComponent");
       SetPerceptionComponent(*SUAIPerceptionComponent);

      RespawnComponent = CreateDefaultSubobject<USURespawnComponent>("RespawnComponent");

       bWantsPlayerState = true;
   }

 

void ASUAI2Controller::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto SUCharacter = Cast<ASUAI2Character>(InPawn))
    {
        RunBehaviorTree(SUCharacter->BehaviorTreeAsset);
    }
}

  void ASUAI2Controller::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ASUAI2Controller::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
