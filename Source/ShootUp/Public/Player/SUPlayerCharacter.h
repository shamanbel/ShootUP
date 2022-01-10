// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Player/SUBaseCharacter.h"
#include "SUPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class SHOOTUP_API ASUPlayerCharacter : public ASUBaseCharacter
{
	GENERATED_BODY()
	
public:
    ASUPlayerCharacter(const FObjectInitializer& ObjInit);
   

protected:
    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CameraCollisionComponent;

   virtual void OnDeath() override;
    virtual void BeginPlay() override;

public:
   virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
       
   virtual bool IsRunning() const override;

private:
    bool HaveToRun = false;
    bool IsMovingForward = false;
    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void StartRuning();
    void StopRuning();

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void CheckCameraOverlap();
};
