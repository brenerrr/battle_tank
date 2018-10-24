// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RotationDirection)
{
	RotationDirection = FMath::Clamp<float>(RotationDirection, -1.f, 1.f);
	float AddedYaw = Speed * RotationDirection  * FApp::GetDeltaTime();

	float NewYaw = AddedYaw + RelativeRotation.Yaw;

	//UE_LOG(LogTemp, Warning, TEXT("RotationDirection: %f, NewElevation: %f"), RotationDirection, NewElevation);
	this->SetRelativeRotation(FRotator(0.f, NewYaw, 0.f));
}


