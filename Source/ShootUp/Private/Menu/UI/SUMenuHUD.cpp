// The numbers lead a dance


#include "Menu/UI/SUMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASUMenuHUD::BeginPlay() 
{
    Super::BeginPlay();

    const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
    if (MenuWidget)
    {
        MenuWidget->AddToViewport();

    }
}
