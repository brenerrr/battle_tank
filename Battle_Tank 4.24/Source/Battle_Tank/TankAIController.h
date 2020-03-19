// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;


/**
 * AI controller
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	 APawn* GetControlledTank() const;

	void AimTowardsPlayer();


protected:
	// Current possessed tank
	APawn* ControlledTank = nullptr;

	// Tank possessed by player
	APawn* PlayerTank = nullptr;

  UTankAimingComponent* AimingComponent;
private:

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  void Tick(float DeltaTime);

  // How close the AI tank can get to the player
  UPROPERTY(EditDefaultsOnly, Category = "Setup")
  float AcceptanceRadius = 3000.f;
};
