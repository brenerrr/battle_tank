// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"

UTankTrack::UTankTrack()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
  Super::BeginPlay();

	TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
  
  //OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  CorrectSidewaysSlipping(DeltaTime);

  }

void UTankTrack::CorrectSidewaysSlipping(float DeltaTime)
{
  // Calculate slippage speed 
  float SidewaysVelocity = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

  // Work-out the required acceleration to correct it
  FVector CorrectionAcceleration = -SidewaysVelocity / DeltaTime * GetRightVector();
  
  // Calculate and apply sideways for (f = m a)
  UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); 
  FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2.f;
  TankRoot->AddForce(CorrectionForce);
}

//void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
//{
//  UE_LOG(LogTemp, Warning, TEXT("I'm hit"));
//}

void  UTankTrack::SetThrottle(float Throttle)
{
	if (!ensureAlways(TankBody)) return;
	// Clamp value between -1 and 1 
	Throttle = FMath::Clamp<float>(Throttle, -1.f, 1.f);


	FVector TrackForce = GetForwardVector() * Throttle * MaxTrackForce;
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


