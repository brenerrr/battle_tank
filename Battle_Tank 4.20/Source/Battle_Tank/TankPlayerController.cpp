// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	bool bIsControlledTankValid = CheckForValidPointer<ATank>(ControlledTank);
	if (bIsControlledTankValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("PLAYER TANK: %s"), *ControlledTank->GetName());
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn()); 
}

template<typename PointerClass>
bool ATankPlayerController::CheckForValidPointer(PointerClass* Pointer ) const
{
	if (Pointer == nullptr) return false;
	else return true; 
}
