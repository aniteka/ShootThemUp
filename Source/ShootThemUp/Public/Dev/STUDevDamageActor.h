// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
public:
	ASTUDevDamageActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Compinents")
		USceneComponent* SceneComponent;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Opt")
        FColor SphereColor = FColor::Green;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Opt")
		float SphereRadius = 300.f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Opt")
		float Damage = 1.f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Opt")
		bool DoFullDamage = false;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Opt")
		TSubclassOf<UDamageType> DamageType;
};
