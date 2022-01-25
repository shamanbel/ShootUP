// The numbers lead a dance


#include "Player/SUPlayerController.h"
#include "Components/SURespawnComponent.h"
#include "SUGameModeBase.h"


void ASUPlayerController::BeginPlay() 
{
    Super::BeginPlay();
    if (GetWorld())
    {
        const auto GameMode = Cast<ASUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &ASUPlayerController::OnMatchStateChanged);
        }
    }
}

//Видимость курсора в различных STATE
void ASUPlayerController::OnMatchStateChanged(ESUMatchState State) 
{
    if (State == ESUMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else 
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

ASUPlayerController::ASUPlayerController() 
{
    RespawnComponent = CreateDefaultSubobject<USURespawnComponent>("RespawnComponent");
}



void ASUPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASUPlayerController::OnPauseGame);
}

void ASUPlayerController::OnPauseGame_Implementation()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->SetPause(this);

}
