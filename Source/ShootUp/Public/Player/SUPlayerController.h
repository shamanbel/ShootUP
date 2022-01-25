// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SUCoreTypes.h"
#include "SUPlayerController.generated.h"

class USURespawnComponent;

UCLASS()
class SHOOTUP_API ASUPlayerController : public APlayerController
{

    GENERATED_BODY()

public:
    ASUPlayerController();

protected:

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "AI")
    USURespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(ESUMatchState State);

};
