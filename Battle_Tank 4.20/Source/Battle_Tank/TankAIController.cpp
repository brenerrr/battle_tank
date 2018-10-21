// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();

	// Check pointers
	bIsControlledTankValid = CheckForValidPointer<ATank>(ControlledTank);
	bIsPlayerTankValid = CheckForValidPointer<ATank>(PlayerTank);

	// Logs
	if (!bIsControlledTankValid) UE_LOG(LogTemp, Error, TEXT("AI CONTROLLER NOT POSSESSING TANK"));
	if (!bIsPlayerTankValid) UE_LOG(LogTemp, Error, TEXT("AI DIDN'T FIND PLAYER TANK"));
	if (bIsControlledTankValid && bIsPlayerTankValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI %s tracking %s"), *ControlledTank->GetName(),*PlayerTank->GetName());
	}
}

void ATankAIController::AimTowardsPlayer()
{
	if (!bIsPlayerTankValid) return;

	FVector PlayerLocation = PlayerTank->GetActorLocation();
	ControlledTank->AimAt(PlayerLocation);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsPlayer();

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

template<typename PointerClass>
bool ATankAIController::CheckForValidPointer(PointerClass* Pointer) const
{
	if (Pointer == nullptr) return false;
	else return true;
}

ATank* ATankAIController::GetPlayerTank() const{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	return Cast<ATank>(PlayerController->GetPawn());
}