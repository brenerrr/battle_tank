// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RotationDirection);
	
private:

	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		// Max elevation of barrel
		float MaxElevation = 60.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		// Min elevation of barrel
		float MinElevation = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		// Barrel movement speed
		float Speed = 5.f;
	
};
