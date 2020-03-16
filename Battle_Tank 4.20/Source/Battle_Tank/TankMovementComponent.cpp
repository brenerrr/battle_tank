// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  if (!LeftTrackToSet || !RightTrackToSet) return;

  LeftTrack = LeftTrackToSet; 
  RightTrack = RightTrackToSet;
}

// TODO PREVENT DOUBLE SPEED WHEN TWO INPUTS ARE GIVEN
void UTankMovementComponent::IntendMoveFoward(float Throw)
{
  if (!LeftTrack || !RightTrack) return;
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(Throw);
  UE_LOG(LogTemp, Warning, TEXT("Intend move foward throw: %f"), Throw);
}

void UTankMovementComponent::IntendMoveClockwise(float Throw)
{
  if (!LeftTrack || !RightTrack) return;
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
  UE_LOG(LogTemp, Warning, TEXT("Intend move left throw: %f"), Throw);
}

