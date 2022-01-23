// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SUMenuPlayerController.generated.h"


UCLASS()
class SHOOTUP_API ASUMenuPlayerController : public APlayerController
{
    GENERATED_BODY()
protected:  

  virtual  void BeginPlay() override;
	
};
