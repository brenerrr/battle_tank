// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Get instance of possessed tank
	ControlledTank = Cast<ATank>(GetPawn());

	// Get instance of tank possessed by player
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn());


	// Logs
	if (ControlledTank == nullptr) UE_LOG(LogTemp, Error, TEXT("AI CONTROLLER NOT POSSESSING TANK"));
	if (PlayerTank == nullptr) UE_LOG(LogTemp, Error, TEXT("AI DIDN'T FIND PLAYER TANK"));
	if ((ControlledTank == nullptr) && (PlayerTank == nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("AI %s tracking %s"), *ControlledTank->GetName(),*PlayerTank->GetName());
	}
}

void ATankAIController::AimTowardsPlayer()
{
	if (ControlledTank == nullptr) return;

	FVector PlayerLocation = PlayerTank->GetActorLocation();
	ControlledTank->AimAt(PlayerLocation);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsPlayer();

	ControlledTank->Fire();

}



