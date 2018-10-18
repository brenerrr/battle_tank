// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();

	bool bIsControlledTankValid = CheckForValidPointer<ATank>(ControlledTank);
	UE_LOG(LogTemp, Warning, TEXT("MyCharacter's Bool is %s"), bIsControlledTankValid ? TEXT("True") : TEXT("False"));

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
