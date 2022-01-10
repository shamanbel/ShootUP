// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SUAIController.generated.h"

class USUAIPerceptionComponent;
class USURespawnComponent;

UCLASS()
class SHOOTUP_API ASUAIController : public AAIController
{
	GENERATED_BODY()


public:
    ASUAIController();

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "AI")
    USUAIPerceptionComponent* SUAIPerceptionComponent;

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "AI")
    USURespawnComponent* RespawnComponent;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "Enemy Actor";

	virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

private:
    AActor* GetFocusOnActor() const;


	
};
