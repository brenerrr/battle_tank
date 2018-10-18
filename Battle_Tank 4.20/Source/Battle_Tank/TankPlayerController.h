// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATank* GetControlledTank() const;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	template <typename PointerClass> bool CheckForValidPointer(PointerClass* Pointer) const;

protected:
	ATank* ControlledTank = nullptr;
	bool IsControlledTankValid = false;
};
