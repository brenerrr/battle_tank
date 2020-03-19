// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "DrawDebugHelpers.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
  if (!ensureAlways (LeftTrackToSet && RightTrackToSet)) return;

  LeftTrack = LeftTrackToSet; 
  RightTrack = RightTrackToSet;
}

// TODO PREVENT DOUBLE SPEED WHEN TWO INPUTS ARE GIVEN
void UTankMovementComponent::IntendMoveFoward(float Throw)
{
  if (!ensureAlways(LeftTrack && RightTrack)) return;

  LeftTrack->AddThrottle(Throw);
  RightTrack->AddThrottle(Throw);
}

void UTankMovementComponent::IntendMoveClockwise(float Throw)
{
  if (!ensureAlways(LeftTrack && RightTrack)) return;
  LeftTrack->AddThrottle(Throw);
  RightTrack->AddThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  UE_LOG(LogTemp, Warning, TEXT("movevelocity of %s: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
  FVector AIForwardIntetion = MoveVelocity.GetSafeNormal();
  FVector TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal() ;

  float FowardIntention = FVector::DotProduct(AIForwardIntetion, TankFoward); 
  FVector RotateIntention = FVector::CrossProduct(AIForwardIntetion, TankFoward);

  IntendMoveClockwise(RotateIntention.Z);
  IntendMoveFoward(FowardIntention);
}