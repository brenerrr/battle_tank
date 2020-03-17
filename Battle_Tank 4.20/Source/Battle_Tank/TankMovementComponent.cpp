// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "DrawDebugHelpers.h"

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
}

void UTankMovementComponent::IntendMoveClockwise(float Throw)
{
  if (!LeftTrack || !RightTrack) return;
  UE_LOG(LogTemp, Warning, TEXT("Rotating amount %f from %s"), Throw, *GetOwner()->GetName());
  LeftTrack->SetThrottle(Throw);
  RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  //UE_LOG(LogTemp, Warning, TEXT("movevelocity of %s: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
  FVector AIForwardIntetion = MoveVelocity.GetSafeNormal();
  FVector TankFoward = GetOwner()->GetActorForwardVector().GetSafeNormal() ;

  float FowardIntention = FVector::DotProduct(AIForwardIntetion, TankFoward); 
  FVector RotateIntention = FVector::CrossProduct(AIForwardIntetion, TankFoward);

  IntendMoveClockwise(RotateIntention.Z);
  IntendMoveFoward(FowardIntention);
  //DrawDebugLine(
  //  GetWorld(),
  //  LeftTrack->GetOwner()->GetActorLocation(),
  //  LeftTrack->GetOwner()->GetActorLocation() + MoveVelocity.GetSafeNormal()*2000.f  ,
  //  FColor::Black,
  //  false,
  //  -1.f,
  //  0,
  //  20.f);
}