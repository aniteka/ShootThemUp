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
        return FMath::IsNearlyZero(Health);
	}

	FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "1", ClampMax = "10000"))
		float MaxHealth = 100.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
		bool AutoHeal = true;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", 
			   meta = (ClampMin = "0.1", ClampMax = "10", EditCondition = "AutoHeal"))
		float HealUpdateTime = 0.3f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", 
			   meta = (ClampMin = "0.1", ClampMax = "20", EditCondition = "AutoHeal"))
		float HealDelay = 3.f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
			   meta = (EditCondition = "AutoHeal"))
		float HealModifier= 1.f;


private:
    float Health = 0.f;
	FTimerHandle HealTimerHandle;
    void HealUpdate();
    void SetHealth(float NewHealth);
	

private:
	// DELEGATE //////////////////////////////////////////////////////////////////////////
	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                             class AController *InstigatedBy, AActor *DamageCauser);

};
