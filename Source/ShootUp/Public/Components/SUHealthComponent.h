// The numbers lead a dance

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SUHealthComponent.generated.h"



DECLARE_MULTICAST_DELEGATE(FOnDeath);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, OnHealthChanged);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);


class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )

class SHOOTUP_API USUHealthComponent : public UActorComponent
{ 
	GENERATED_BODY()

public:	
	USUHealthComponent();

	FOnDeath OnDeath;

   // UPROPERTY(BlueprintAssignable)
    FOnHealthChanged OnHealthChanged;
   

	UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const { return Health <= 0.0f;}

	UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; 0.0f; }

    UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }	  

	bool TryToAddHealth(float HealthAmount);
    bool IsHealthFull() const;

protected:

	 UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    TMap<UPhysicalMaterial*, float> DamageModifiers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin ="0", ClampMax = "100.0"))
	float MaxHealth = 100.0f;
	virtual void BeginPlay() override;

    UPROPERTY(Replicated)
    float Health = 0.0f;

private:
 

	UFUNCTION()
    void OnTakeAnyDamage
	(
	AActor* DamagedActor,							//
    float Damage,									//
    const class UDamageType* DamageType,			//
    class AController* InstigatedBy,				//
    AActor* DamageCauser
	);
	
    
	void SetHealth(float NewHealth);
	void Killed(AController* KillerController);
    void ReportDamageEvent(float Damage, AController* InstigatedBy);

	UFUNCTION()
    void OnTakePointDamage
	(
	AActor* DamagedActor,						//
	float Damage,								//
	class AController* InstigatedBy,			//
	FVector HitLocation,						//
	class UPrimitiveComponent* FHitComponent,	//
	FName BoneName,								//
	FVector ShotFromDirection,					//
	const class UDamageType* DamageType,		//
	AActor* DamageCauser
	);
    
	UFUNCTION()
    void OnTakeRadialDamage
	(
	AActor* DamagedActor,					//
	float Damage,							//
	const class UDamageType* DamageType,	//
	FVector Origin,							//
	FHitResult HitInfo,						//
	class AController* InstigatedBy,		//
	AActor* DamageCauser 
	);

	void ApplyDamage(float Damage, AController* InstigatedBy);
    float GetPointDamageModifier(AActor* DamageActor, const FName& BoneName);
};
