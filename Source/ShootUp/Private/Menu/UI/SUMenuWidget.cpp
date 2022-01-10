// The numbers lead a dance


#include "Menu/UI/SUMenuWidget.h"
#include "Components/Button.h"

#include "SUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuWidget, All, All);

void USUMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USUMenuWidget::ONStartGame);
    }
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USUMenuWidget::ONQuitGame);
    }
}



void USUMenuWidget::ONStartGame() 
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound); 
   
}

void USUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if (!GetWorld()) return;
    if (Animation != HideAnimation) return;
    const auto SUGameInstance = GetWorld()->GetGameInstance<USUGameInstance>();
    if (!SUGameInstance) return;

    if (SUGameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogMenuWidget, Error, TEXT("Level Name is none"));
        return;
    }

    UGameplayStatics::OpenLevel(this, SUGameInstance->GetStartupLevelName());
}

void USUMenuWidget::ONQuitGame() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
