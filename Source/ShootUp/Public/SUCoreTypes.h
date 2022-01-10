#pragma once

#include "SUCoreTypes.generated.h"

// weapon
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;  // ���������� �������� � ��������

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Clips;  // ���������� ��������� � ���������
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayersNum = 2;  //���� �������� - ����� � ������ NPS

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "600"))
    int32 RoundTime = 10;  //� ��������

   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
   int32 RoundsNum = 4;

   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
   int32 RespawnTime = 5;//� ��������
};

UENUM(BlueprintType)
enum class ESUMatchState: uint8
{
    WaitingToStart = 0,
    InProgress,
    Pause,
    GameOver
};
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESUMatchState);
