// The numbers lead a dance

#include "UI/SUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"

#include "Components/Image.h"


 void USUPlayerStatRowWidget::SetPlayerName(const FText& Text)
 {
     if (!PlayerNameTextBlock) return;
     PlayerNameTextBlock->SetText(Text);
 }

void USUPlayerStatRowWidget::SetKills(const FText& Text)
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

 void USUPlayerStatRowWidget::SetDeaths(const FText& Text)
 {
     if (!DeathsTextBlock) return;
     DeathsTextBlock->SetText(Text);
 }

 void USUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
 {
     if (!PlayerIndicatorImage) return;

     PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

 };
