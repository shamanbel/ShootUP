// The numbers lead a dance


#include "UI/SUPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include "Components/Button.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


void USUPauseWidget::NativeOnInitialized()
{
Super::NativeOnInitialized();

	if(ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &USUPauseWidget::OnClearPause);
    }

}

void USUPauseWidget::OnClearPause() 
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    
    GetWorld()->GetAuthGameMode()->ClearPause();
    
}
