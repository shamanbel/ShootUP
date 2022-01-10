// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SUEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*)
UCLASS()
class SHOOTUP_API USUEquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
    FOnNotifiedSignature OnNotified;

};
