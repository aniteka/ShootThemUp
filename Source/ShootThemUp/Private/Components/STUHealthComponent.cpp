// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHeal, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHealth(MaxHealth);

    // Bind delegate
    AActor *ComponentOwner = GetOwner();
    if (ComponentOwner)
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamageHandle);
}

void USTUHealthComponent::OnTakeAnyDamageHandle(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                                AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage < 0 || IsDead())
        return;
    
    if (AutoHeal)
        GetWorld()
            ->GetTimerManager()
            .ClearTimer(HealTimerHandle);

    SetHealth(Health - Damage);

    if (!IsDead() && AutoHeal)
        GetWorld()
            ->GetTimerManager()
            .SetTimer(HealTimerHandle, 
                      this, 
                      &USTUHealthComponent::HealUpdate,
                      HealUpdateTime,
                      true,
                      HealDelay);

    if (IsDead())
        OnDeath.Broadcast();
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (FMath::IsNearlyEqual(Health,MaxHealth))
        GetWorld()
            ->GetTimerManager()
            .ClearTimer(HealTimerHandle);
}
void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
