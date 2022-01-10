// The numbers lead a dance


#include "Components/SUCharacterMovementComponent.h"
#include "Player/SUBaseCharacter.h"

float USUCharacterMovementComponent::GetMaxSpeed() const 
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASUBaseCharacter* Player = Cast<ASUBaseCharacter>(GetPawnOwner());

    return Player && Player -> IsRunning() ? MaxSpeed * RunModifier :MaxSpeed;
}
