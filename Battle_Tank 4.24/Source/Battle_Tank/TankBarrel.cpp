// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Misc/App.h"

void UTankBarrel::Elevate(float RotationDirection)
{
	RotationDirection = FMath::Clamp<float>(RotationDirection, -FApp::GetDeltaTime()*Speed, FApp::GetDeltaTime()*Speed);
	float AddedElevation =  RotationDirection ;

	float NewElevation = AddedElevation + RelativeRotation.Pitch;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevation, MaxElevation);

	this->SetRelativeRotation(FRotator(NewElevation,0.f,0.f));
}


