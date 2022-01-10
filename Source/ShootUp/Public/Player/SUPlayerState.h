// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SUPlayerState.generated.h"


UCLASS()
class SHOOTUP_API ASUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; }
    int32 GetTeamID() const { return TeamID; }

	void AddKill() { ++KillsNum; }
    int32 GetKillsNum() const { return KillsNum; } 
    void AddDeath() { ++DeathsNum; }
    int32 GetDeathsNum() const { return DeathsNum; } 

    void LogInfo();
	

private:
    int32 TeamID;
	int32 KillsNum = 0;
    int32 DeathsNum = 0;

	

	
};
