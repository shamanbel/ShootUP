// The numbers lead a dance


#include "Menu/SUMenuPlayerController.h"
#include "SUGameInstance.h"

void ASUMenuPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;


}
