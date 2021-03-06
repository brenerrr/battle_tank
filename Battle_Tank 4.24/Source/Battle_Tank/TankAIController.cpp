// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get instance of possessed tank
	ControlledTank = GetPawn();

	// Get instance of tank possessed by player
	PlayerTank = UGameplayStatics::GetPlayerController(this, 0)->GetPawn();

  AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	// Logs
  if (!ensure(ControlledTank)) return;
  if (!ensure(AimingComponent)) return;
  if (!ensure(PlayerTank)) return;
}

void ATankAIController::AimTowardsPlayer()
{
	if (!ensureAlways(ControlledTank)) return;

	FVector PlayerLocation = PlayerTank->GetActorLocation();
	AimingComponent->AimAt(PlayerLocation);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsPlayer();

  if (PlayerTank)
  {
    MoveToActor(PlayerTank, AcceptanceRadius);
  }
	
  // If aim or locked
  if (!ensure(AimingComponent)) return; 

  if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) AimingComponent->Fire();

}



