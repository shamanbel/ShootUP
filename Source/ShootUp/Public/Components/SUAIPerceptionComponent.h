// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SUAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTUP_API USUAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

	public:
		
		AActor* GetClosestEnemy() const;
	
};
