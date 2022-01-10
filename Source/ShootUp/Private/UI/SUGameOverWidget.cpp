// The numbers lead a dance


#include "UI/SUGameOverWidget.h"
#include "SUGameModeBase.h"
#include "Player/SUPlayerState.h"
#include "SUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include  "SUUtils.h"
#include  "Components/Button.h"
#include  "Kismet/gameplayStatics.h"


void USUGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetWorld())
    {
        const auto GameMode = Cast<ASUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &USUGameOverWidget::OnMatchStateChanged);
        }
    }
    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &USUGameOverWidget::OnResetLevel);
    }
}

void USUGameOverWidget::OnMatchStateChanged(ESUMatchState State) 
{
    if (State == ESUMatchState::GameOver)
    {
        UpdatePlayerState();
    }
}

void USUGameOverWidget::UpdatePlayerState() 
{
    if (!GetWorld() || !PlayerStatBox) return;
    PlayerStatBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASUPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;
        const auto PlayerStateRowWidget = CreateWidget<USUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStateRowWidget) continue;

        PlayerStateRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStateRowWidget->SetKills(SUUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStateRowWidget->SetDeaths(SUUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStateRowWidget);
    }
    
}

void USUGameOverWidget::OnResetLevel() 
{
    //const FName CurrentLevelName = "TestLevel";
    const FString CurrentLevelName = UGameplayStatics ::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
