// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "Runtime/Engine/Public/UnrealClient.h"
#include "TankAimingComponent.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

  // Get viewport and bind rezising event to UpdateScreenSize function
	FViewport* Viewport = GEngine->GameViewport->Viewport;
	Viewport->ViewportResizedEvent.AddUObject(this, &ATankPlayerController::UpdateViewportSize);
	UpdateViewportSize( Viewport, 0);

  AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

  if (!ensure(AimingComponent)) return;
  FoundAimingComponent(AimingComponent); 
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!ensureAlways(AimingComponent)) return;
	// Get world location of where crosshair is pointing at
	FVector HitLocation(0.0f,0.0f,0.0f);
	bool bIsDeprojectValid = GetSightRayHitLocation(HitLocation);
	if (bIsDeprojectValid) AimingComponent->AimAt(HitLocation);

}


UFUNCTION()
void ATankPlayerController::UpdateViewportSize( FViewport* Viewport,  uint32 index)
{
	GetViewportSize(XScreen, YScreen);
	UE_LOG(LogTemp, Warning, TEXT("Screen resolution: %d x %d"), XScreen, YScreen);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation)
{
	// Deproject crosshair into 3D space 
	FVector CameraLocation(0.0f, 0.0f, 0.0f), CameraDirection(0.0f, 0.0f, 0.0f);
	bool bIsDeprojectValid = false;

	// Get camera location and direction
	bIsDeprojectValid = DeprojectScreenPositionToWorld(
		XCrosshair*XScreen,
		YCrosshair*YScreen,
		CameraLocation,
		CameraDirection);
  
	// Line trace from camera 
	FHitResult LineTraceResult;
	ECollisionChannel CollisionChannel(ECC_WorldStatic);
	FCollisionQueryParams CollisionQueryParams();
	FCollisionResponseParams CollisionResponseParams;
	bool bIsLineTraceValid = GetWorld()->LineTraceSingleByChannel(
		LineTraceResult,
		CameraLocation,
		CameraDirection.GetSafeNormal()*500000.f + CameraLocation,
		CollisionChannel,
		CollisionQueryParams,
		CollisionResponseParams
		);

	HitLocation = LineTraceResult.Location;

	if (bIsLineTraceValid) 
	{
		DrawDebugSphere(GetWorld(), HitLocation, 200.f, 50, FColor::Purple);
	}
	
	return bIsDeprojectValid;
}

