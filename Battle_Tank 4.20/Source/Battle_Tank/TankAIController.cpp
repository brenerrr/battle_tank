// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


// Called when the game starts or when spawned
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	bool bIsControlledTankValid = CheckForValidPointer<ATank>(ControlledTank);
	if (bIsControlledTankValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI TANK: %s"), *ControlledTank->GetName());
	}
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
