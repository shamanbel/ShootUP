// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/SUBaseWeapon.h"
#include "SUWeaponComponent.generated.h"

class ASUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTUP_API USUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USUWeaponComponent();

	void StartFire();
    void StartFireAI();
    void StopFire();
    
    
    void NextWeapon();
    void Reload();
    bool GetWeaponUIData(FWeaponUIData& UIData) const; 
    bool GetWeaponAmmoData(FAmmoData& AmmoData) const; 
   
    bool TryToAddAmmo(TSubclassOf<ASUBaseWeapon> WeaponType, int32 ClipsAmount);

   void Zoom(bool Enabled);

protected:
	
   UPROPERTY(EditDefaultsOnly, Category = "Weapon")
   TArray<TSubclassOf<ASUBaseWeapon>> WeaponClasses;

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
   FName WeaponEquipSocketName = "WeaponSocket";

  UPROPERTY(EditDefaultsOnly, Category = "Weapon")
   FName WeaponArmorySocketName = "ArmorySocket";

  UPROPERTY(EditDefaultsOnly, Category = "Animation")
  UAnimMontage* EquipAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
  UAnimMontage* ReloadAnimMontage;
  ;


virtual void BeginPlay() override;
virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	UPROPERTY()
    ASUBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ASUBaseWeapon*> Weapons;

    void SpawnWeapons();

    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void InitAnimations();
    void AttachWeaponToSocket(ASUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName); 
	void EquipWeapon(int32 WeaponIndex);//ѕрикрепл€ет оружие к сокету

    void PlayAnimMontage(UAnimMontage* Animation);

    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;
    void OnEmptyClip(ASUBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();//перезар€дка

};
