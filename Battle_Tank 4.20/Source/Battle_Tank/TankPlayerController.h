// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;


/**
 * 
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	// Get tank controlled by this controller
	ATank* GetControlledTank() const;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	template <typename PointerClass> bool CheckForValidPointer(PointerClass* Pointer) const;

	// Aim in the direction of crosshair
	void AimTowardsCrosshair() ;

	

protected:
	ATank* ControlledTank = nullptr;

	// Update variables that store viewport size
	void UpdateViewportSize(FViewport*, uint32);

	// Screen position of crosshair
	float XCrosshair = 0.5f;
	float YCrosshair = 0.33333f; 

	// Get hit location from raytrace spawned from crosshair
	bool GetSightRayHitLocation(FVector &HitLocation);

	// Screen dimensions
	int32 XScreen, YScreen;

};
