// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for translating player input aim to tank
 */
UCLASS()
class BATTLE_TANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	template <typename PointerClass> bool CheckForValidPointer(PointerClass* Pointer) const;

	// Aim in the direction of crosshair
	void AimTowardsCrosshair() ;

	

protected:

	// Update variables that store viewport size
	void UpdateViewportSize(FViewport*, uint32);

	// Screen position of crosshair
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		// Crosshair position X axis
		float XCrosshair = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		// Crosshair position Y axis
		float YCrosshair = 0.33333f; 

	// Get hit location from raytrace spawned from crosshair
	bool GetSightRayHitLocation(FVector &HitLocation);

	// Screen dimensions
	int32 XScreen, YScreen;

  UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

  UTankAimingComponent* AimingComponent = nullptr;

};
