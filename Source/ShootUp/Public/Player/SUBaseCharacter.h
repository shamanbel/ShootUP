// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SUBaseCharacter.generated.h"

class USUHealthComponent;
class USUWeaponComponent;

UCLASS()
class SHOOTUP_API ASUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	ASUBaseCharacter(const FObjectInitializer& ObjInit);

protected:

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USUHealthComponent* HealthComponent;

	//UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
 //   UTextRenderComponent* HealthTextComponent;

    UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
    USUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

 /*   UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASUBaseWeapon> WeaponClass;*/

	virtual void OnDeath();
	virtual void OnHealthChanged(float Health);
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
    virtual void TurnOff() override; 
	 virtual void Reset() override; 
	UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;
};
