// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
  // Bind tracks to movement component
  UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

  // Process the intetion of moving foward
  UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendMoveFoward(float Throw);

  UFUNCTION(BlueprintCallable, Category = "Input")
    void IntendMoveClockwise(float Throw);

private: 

  // Called from the pathfinding logic by the AI controllers
  virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


  UTankTrack* LeftTrack = nullptr;
  UTankTrack* RightTrack = nullptr;

	
	
	
};
