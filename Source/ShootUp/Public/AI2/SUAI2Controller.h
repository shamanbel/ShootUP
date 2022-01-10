// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SUAI2Controller.generated.h"

class USUAIPerceptionComponent;
class USURespawnComponent;

UCLASS()
class SHOOTUP_API ASUAI2Controller : public AAIController
{
	GENERATED_BODY()

public:

    ASUAI2Controller();

protected:

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "AI")
    USUAIPerceptionComponent* SUAIPerceptionComponent;

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "AI")
    USURespawnComponent* RespawnComponent;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor"; 

	virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
	
private:
    AActor* GetFocusOnActor() const;
};
