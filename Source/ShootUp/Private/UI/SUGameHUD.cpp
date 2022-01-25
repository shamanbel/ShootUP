// The numbers lead a dance


#include "UI/SUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "SUGameModeBase.h"



void ASUGameHUD::DrawHUD() 
{
    Super::DrawHUD();
}

void ASUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(ESUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair: GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<ASUGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
        GameMode->OnMatchStateChanged.AddUObject(this, &ASUGameHUD::OnMatchStateChanged);
        }
    }

}


void ASUGameHUD::DrawCross() 
{
     const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Black;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void ASUGameHUD::OnMatchStateChanged(ESUMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
}