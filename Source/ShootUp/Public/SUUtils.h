#pragma once
#include "Player/SUPlayerState.h"

class SUUtils
{
public:
	
	template<typename T> 
	static T* GetSUPlayerComponent(AActor* PlayerPawn)
    {
       if (!PlayerPawn) return nullptr;

       const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
       return Cast<T>(Component);
	}

    //определяет противника
	 bool static AreEnemies(AController* Controller01, AController* Controller02)
    {
        if (!Controller01 || !Controller02 || Controller01 == Controller02) return false;

        const auto PlayerState1 = Cast<ASUPlayerState>(Controller01->PlayerState);
        const auto PlayerState2 = Cast<ASUPlayerState>(Controller02->PlayerState);

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }
    static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }

};

