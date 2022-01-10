// The numbers lead a dance


#include "SUGameModeBase.h"
#include "Player/SUBaseCharacter.h"
#include "Player/SUPlayerController.h"
#include "UI/SUGameHUD.h"
#include "AIController.h"
#include "Player/SUPlayerState.h"
#include "SUUtils.h"
#include "EngineUtils.h"
#include "Components/SURespawnComponent.h"
#include "Components/SUWeaponComponent.h"
#include "SUGameInstance.h"


DEFINE_LOG_CATEGORY_STATIC(LogModeBase, All, All);

 ASUGameModeBase::ASUGameModeBase() 
 {
     DefaultPawnClass = ASUBaseCharacter::StaticClass();
     PlayerControllerClass = ASUPlayerController::StaticClass();
     HUDClass = ASUGameHUD::StaticClass();
     PlayerStateClass = ASUPlayerState::StaticClass();
 }

 

void ASUGameModeBase::StartPlay() 
{
    Super::StartPlay();
    
    SpawnBots();
    CreateTeamsInfo();//–аспределение по командам
    CurrentRound = 1;
    StartRound();

    SetMatchState(ESUMatchState::InProgress);
}

 UClass* ASUGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController) 
 {
     if (InController && InController->IsA<AAIController> ())
     {
         return AIPawnClass;
     }
     return Super::GetDefaultPawnClassForController_Implementation(InController);
 }



void ASUGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {

        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto SUAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(SUAIController);//спаунит игрока
    }
}

void ASUGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASUGameModeBase::GameTimerUpdate, 1.0f, true);

}

void ASUGameModeBase::GameTimerUpdate() 
{
    UE_LOG(LogModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);
    
   /* const auto TimerRate = GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
    RoundCountDown = TimerRate;*/
    if (--RoundCountDown ==0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {

            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else 
        {
            GameOver();
        }
    }
}

 void ASUGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
};
void ASUGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
}
void ASUGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for(auto It = GetWorld()-> GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "NPS");

        TeamID = TeamID == 1 ? 2 : 1;
    }
    
}


void ASUGameModeBase::Killed(AController* KillerController, AController* VictimController) 
{
    const auto KillerPlayerState = KillerController ? Cast<ASUPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ASUPlayerState>(VictimController->PlayerState) : nullptr;
    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }
    StartRespawn(VictimController);
}

void ASUGameModeBase::LogPlayerInfo()
{
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        if (!GetWorld()) return;
        const auto Controller = It->Get();
        if (!Controller) continue;
        const auto PlayerState = Cast<ASUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void ASUGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnComponent = SUUtils::GetSUPlayerComponent<USURespawnComponent>(Controller);
    if (!RespawnComponent) return;
    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASUGameModeBase::RespawnRequest(AController* Controller) 
{
    ResetOnePlayer(Controller);
}


void ASUGameModeBase::GameOver()
{
    UE_LOG(LogModeBase, Display, TEXT("_________GAME OVER_______"));
    LogPlayerInfo();

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    SetMatchState(ESUMatchState::GameOver);
}

void ASUGameModeBase::SetMatchState(ESUMatchState State)
{
    if (MatchState == State) return;

    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}

void ASUGameModeBase::StopAllFire() 
{
    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        const auto WeaponComponent = SUUtils::GetSUPlayerComponent<USUWeaponComponent>(Pawn);
        if (!WeaponComponent) continue;

        WeaponComponent->StopFire();
        WeaponComponent->Zoom(false);
    }
}

bool ASUGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    
    if(PauseSet)
    {
        SetMatchState(ESUMatchState::Pause);
    }
    
    return PauseSet;
}

bool ASUGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(ESUMatchState::InProgress);
    }
    return PauseCleared;
}
