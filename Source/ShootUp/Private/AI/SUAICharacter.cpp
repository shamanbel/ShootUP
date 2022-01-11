// The numbers lead a dance


#include "AI/SUAICharacter.h"
#include "AI/SUAIController.h"
#include  "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ASUAICharacter::ASUAICharacter(const FObjectInitializer& ObjInit)                       //
    : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASUAIController::StaticClass();
}

void ASUAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto SUController = Cast<AAIController>(Controller);
    if (SUController && SUController-> BrainComponent)
    {
        SUController->BrainComponent->Cleanup();
    }
}

