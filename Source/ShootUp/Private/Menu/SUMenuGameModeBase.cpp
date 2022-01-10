// The numbers lead a dance


#include "Menu/SUMenuGameModeBase.h"
#include "Menu/SUMenuPlayerController.h"
#include "Menu/UI/SUMenuHUD.h"

ASUMenuGameModeBase::ASUMenuGameModeBase()
{
    PlayerControllerClass = ASUMenuPlayerController::StaticClass();
    HUDClass = ASUMenuHUD::StaticClass();

}

