// The numbers lead a dance


#include "Animations/SUEquipFinishedAnimNotify.h"

void USUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)

{
    OnNotified.Broadcast(MeshComp);
    //MeshComp
    Super::Notify(MeshComp, Animation);
}