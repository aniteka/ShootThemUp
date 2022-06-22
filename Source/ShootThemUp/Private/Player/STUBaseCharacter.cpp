// Shoot Them Up Game. All Rights Reserved.

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjInit)
    : Super(
          ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
    , CameraComponent(CreateDefaultSubobject<UCameraComponent>("CameraComponent"))
    , SpringArmComponent(CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent"))
    , HealthComponent(CreateDefaultSubobject<USTUHealthComponent>("HealthComponent"))
    , HealthTextComponent(CreateDefaultSubobject<UTextRenderComponent>("HealthTextCompoenent"))
{
    PrimaryActorTick.bCanEverTick = true;

    // Setup Attachment
    SpringArmComponent->SetupAttachment(GetRootComponent());
    CameraComponent->SetupAttachment(SpringArmComponent);
    HealthTextComponent->SetupAttachment(GetRootComponent());

    // Options
    SpringArmComponent->bUsePawnControlRotation = true;
}

void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());
    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent
        ->OnHealthChanged
        .AddUObject(this, 
                    &ASTUBaseCharacter::OnHealthChanged);
}

void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASTUBaseCharacter::StopJumping);

    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::SprintEnd);
}

bool ASTUBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween   = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct   = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees        = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASTUBaseCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASTUBaseCharacter::SprintStart()
{
    WantsToRun = true;
}

void ASTUBaseCharacter::SprintEnd()
{
    WantsToRun = false;
}
void ASTUBaseCharacter::OnDeath()
{
    UE_LOG(LogTemp, Display, TEXT("Character is dead"));

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}
