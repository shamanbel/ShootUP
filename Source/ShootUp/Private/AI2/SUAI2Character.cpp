// The numbers lead a dance


#include "AI2/SUAI2Character.h"
#include "AI2/SUAI2Controller.h"
#include "BrainComponent.h"



ASUAI2Character::ASUAI2Character(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASUAI2Controller::StaticClass();
    SetReplicates(true);

}


void ASUAI2Character::OnDeath()
{
    Super::OnDeath();

    const auto SUController = Cast<AAIController>(Controller);
    if (SUController && SUController->BrainComponent)
    {
        SUController->BrainComponent->Cleanup();
    }
}
