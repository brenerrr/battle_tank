// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	void Rotate(float RotationDirection);

private:

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		// Barrel movement speed
		float Speed = 5.f;
};
