// The numbers lead a dance


#include "UI/SUGameDataWidget.h"
#include "SUGameModeBase.h"
#include "Player/SUPlayerState.h"

 int32  USUGameDataWidget::GetKillsNum() const 
 {
     const auto PlayerState = GetSUPlayerState();
     return PlayerState ? PlayerState->GetKillsNum() : 0;
 };

int32 USUGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetSUGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;

}

int32 USUGameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetSUGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USUGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetSUGameMode();
        return GameMode ? GameMode->GetRoundSecondRemaining() : 0;
}

ASUGameModeBase* USUGameDataWidget::GetSUGameMode() const
{
    return GetWorld() ? Cast<ASUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASUPlayerState* USUGameDataWidget::GetSUPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
