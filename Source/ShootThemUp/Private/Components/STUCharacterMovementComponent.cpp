// Shoot Them Up Game. All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    auto MaxSpeed = Super::GetMaxSpeed();

    const ASTUBaseCharacter *Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

    return 
        Player && 
        Player->IsRunning() ? 
            MaxSpeed * RunModifier : 
            MaxSpeed;
}
