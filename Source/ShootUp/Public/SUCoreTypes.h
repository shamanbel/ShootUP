#pragma once

#include "SUCoreTypes.generated.h"

// weapon
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;  //  оличество патронов в магазине

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Clips;  //  оличество магазинов в боезапасе
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayersNum = 2;  //ќдин персонаж - игрок и второй NPS

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "600"))
    int32 RoundTime = 10;  //в секундах

   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "10"))
   int32 RoundsNum = 4;

   UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "20"))
   int32 RespawnTime = 5;//в секундах
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
