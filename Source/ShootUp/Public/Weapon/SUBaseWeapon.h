// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SUCoreTypes.h"
#include "SUBaseWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, ASUBaseWeapon*);

class USkeletalMeshComponent;
class USoundCue; 


USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};


UCLASS()
class SHOOTUP_API ASUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	ASUBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;
    virtual void StartFire();
    virtual void StartFireAI();
    virtual void StopFire();
    
    bool IsFiring() const;

   void ChangeClip();
   bool CanReload() const;
   FWeaponUIData GetUIData() const { return UIData; }

   FAmmoData GetAmmoData() const { return CurrentAmmo; }

   bool TryToAddAmmo(int32 ClipsAmount);

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 2000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{9, 2};//Устанавливаем кол патронов и магазинов

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float DamageAmount = 20.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,  Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    USoundCue* FireSound;

	virtual void BeginPlay() override;

	virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd); 
    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    bool IsAmmoFull() const;
   

    virtual void Zoom(bool Enabled){}
    
    void LogAmmo();
private:
    FAmmoData CurrentAmmo;

protected:
   
    bool FireInProgress = false;
};
