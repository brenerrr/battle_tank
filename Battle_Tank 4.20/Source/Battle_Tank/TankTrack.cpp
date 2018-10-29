// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void  UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("Throttle set to: %f"), Throttle);
	//TODO Clamp value between -1 and 1 
}


