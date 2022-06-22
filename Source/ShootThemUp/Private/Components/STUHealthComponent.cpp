// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHeal, All, All);

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    OnHealthChanged.Broadcast(Health);
    
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
    Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
    OnHealthChanged.Broadcast(Health);

    if (IsDead())
        OnDeath.Broadcast();
}
