// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Misc/App.h"

void UTankBarrel::Elevate(float RotationDirection)
{
	RotationDirection = FMath::Clamp<float>(RotationDirection, -1.f, 1.f);
	float AddedElevation = Speed * RotationDirection  * FApp::GetDeltaTime();

	float NewElevation = AddedElevation + RelativeRotation.Pitch;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevation, MaxElevation);

	UE_LOG(LogTemp, Warning, TEXT("RotationDirection: %f, NewElevation: %f"), RotationDirection, NewElevation);
	this->SetRelativeRotation(FRotator(NewElevation,0.f,0.f));
}


