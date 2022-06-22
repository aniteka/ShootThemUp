// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	USTUHealthComponent();


protected:
	virtual void BeginPlay() override;


public:	
	UFUNCTION(BlueprintCallable)	
	float GetHealth() const
    {
        return Health;
	}

	UFUNCTION(BlueprintCallable)
    bool IsDead() const
    {
        return Health <= 0;
	}

	FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "1", ClampMax = "10000"))
		float MaxHealth = 100.f;


private:
    float Health = 0.f;
	

private:
	// DELEGATE //////////////////////////////////////////////////////////////////////////
	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                             class AController *InstigatedBy, AActor *DamageCauser);

};