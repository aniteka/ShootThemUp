// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	ASTUBaseCharacter(const FObjectInitializer& ObjInit);


protected:
	virtual void BeginPlay() override;


public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:	
	// PUBLIC FUNCTIONS //////////////////////////////////////////////////////////////////////////
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsRunning() const;
	UFUNCTION(BlueprintCallable, Category = "Movement")
		float GetMovementDirection() const;


protected:
	// COMPONENTS //////////////////////////////////////////////////////////////////////////
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
        class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class USTUHealthComponent* HealthComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UTextRenderComponent* HealthTextComponent;
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
		UAnimMontage *DeathAnimMontage; 
			


private:
	// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////
	void MoveForward(float Amount);
	void MoveRight(float Amount);
    void SprintStart();
    void SprintEnd();
    void OnDeath();
    void OnHealthChanged(float Health);


private:
	// PRIVATE VARIBLES //////////////////////////////////////////////////////////////////////////
	bool WantsToRun = false;
    bool IsMovingForward = false;


};
