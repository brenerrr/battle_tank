// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"

UTankTrack::UTankTrack()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
  Super::BeginPlay();

	TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//  }

void UTankTrack::CorrectSidewaysSlipping()
{
  // Calculate slippage speed 
  float SidewaysVelocity = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

  // Work-out the required acceleration to correct it
  FVector CorrectionAcceleration = -SidewaysVelocity / GetWorld()->GetDeltaSeconds() * GetRightVector();
  
  // Calculate and apply sideways for (f = m a)
  UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); 
  FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2.f;
  TankRoot->AddForce(CorrectionForce);
}

// Called every frame in which the tank is touching the ground
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  UE_LOG(LogTemp, Warning, TEXT("I'm hit"));
  CorrectSidewaysSlipping();
  DriveTrack();

  // Reset throttle 
  CurrentThrottle = 0;
}

void  UTankTrack::AddThrottle(float Throttle)
{
	if (!ensureAlways(TankBody)) return;
  CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::DriveTrack()
{
  // Clamp value between -1 and 1 
  FVector TrackForce = GetForwardVector() * CurrentThrottle * MaxTrackForce;
  FVector ForceLocation = GetComponentLocation();

  TankBody->AddForceAtLocation(TrackForce, ForceLocation);

  if (bDebug)
  {
    DrawDebugDirectionalArrow(
      GetWorld(),
      ForceLocation,
      ForceLocation + TrackForce,
      10.f,
      FColor::Blue,
      false,
      -1.f,
      0,
      10.f);
  }
}


