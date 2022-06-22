// Shoot Them Up Game. All Rights Reserved.


#include "Dev/STUDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASTUDevDamageActor::ASTUDevDamageActor()
    : SceneComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"))
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(SceneComponent);
}

void ASTUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(),
                                        Damage,
                                        GetActorLocation(),
                                        SphereRadius,
                                        DamageType,
                                        {},
                                        this,
                                        nullptr,
                                        DoFullDamage);
}

