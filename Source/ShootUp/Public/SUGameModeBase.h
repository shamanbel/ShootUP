// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SUCoreTypes.h"

#include "SUGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTUP_API ASUGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    ASUGameModeBase();
    FOnMatchStateChangedSignature OnMatchStateChanged;
    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    void Killed(AController* KillerController, AController* VictimController);
    void RespawnRequest(AController* Controller);
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    
    FGameData GetGameData() const { return GameData; }
    int32 GetCurrentRoundNum() const { return CurrentRound; }
    int32 GetRoundSecondRemaining() const { return RoundCountDown; }

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:

    ESUMatchState MatchState = ESUMatchState::WaitingToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();
    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);
    void CreateTeamsInfo();//������������� �� ��������
    void LogPlayerInfo();
    void StartRespawn(AController* Controller);
    void GameOver();
    void SetMatchState(ESUMatchState State);
    void StopAllFire();
};
