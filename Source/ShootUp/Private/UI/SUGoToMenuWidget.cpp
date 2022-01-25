// The numbers lead a dance


#include "UI/SUGoToMenuWidget.h"
#include "Components/Button.h"
#include "SUGameInstance.h"
#include "Kismet/GameplayStatics.h"


void USUGoToMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USUGoToMenuWidget::OnGoToMenu);
    }

}

void USUGoToMenuWidget::OnGoToMenu() 
{
    if (!GetWorld()) return;

      const auto SUGameInstance = GetWorld()->GetGameInstance<USUGameInstance>();
    if (!SUGameInstance) return;

    if (SUGameInstance->GetMenuLevelName().IsNone())
    {
    return;
    }

    UGameplayStatics::OpenLevel(this, SUGameInstance->GetMenuLevelName());
}
