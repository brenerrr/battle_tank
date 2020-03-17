// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"

void UTankTrack::BeginPlay()
{
	TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void  UTankTrack::SetThrottle(float Throttle)
{
	if (TankBody == nullptr) return;
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


