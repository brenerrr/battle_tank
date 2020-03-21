// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
  Tank = GetOwner();
  
  LastTimeFired = GetWorld()->GetTimeSeconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  UpdateFiringStatus();
}

void UTankAimingComponent::UpdateFiringStatus()
{
  if (GetWorld()->GetTimeSeconds() - LastTimeFired < 60.f / FireRate) FiringStatus = EFiringStatus::Reloading;
  else if (IsBarrelMoving()) FiringStatus = EFiringStatus::Aiming;
  else FiringStatus = EFiringStatus::Locked;
}

void UTankAimingComponent::AimAt(FVector& AimLocation)
{
  if (!ensureAlways(Barrel)) return; 

	// Calculate toss direction to hit aimlocation with launchspeed
	TArray<AActor*> ActorsToIgnore;	ActorsToIgnore.Add(Tank);

	bool bIsShotValid = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		AimDirection,
		Barrel->GetSocketLocation(FName("EndBarrel")), // ATENTION, BARREL MUST HAVE SOCKET NAMED ENDBARREL
		AimLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		bDebug
	); 

	// Move towards toss direction
	if (bIsShotValid)	MoveBarrelTowards();
}

bool UTankAimingComponent::IsBarrelMoving()
{
  if (!ensureAlways(Barrel)) return false;

  FVector BarrelFoward = Barrel->GetForwardVector().GetSafeNormal();

  // Check if vectors are close
  if (AimDirection.GetSafeNormal().Equals(BarrelFoward, 0.1f)) return false; 
  else return true;

}

void UTankAimingComponent::MoveBarrelTowards()
{
  if (!ensureAlways(Barrel && Turret)) return;

	// Compute the difference between current barrel direction and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation() ;
	FRotator AimRotator = AimDirection.Rotation();
	FRotator Delta = AimRotator - BarrelRotator;

  if (FMath::Abs(Delta.Yaw) > 180.f) Delta.Yaw   = - Delta.Yaw;
	Barrel->Elevate(Delta.Pitch);
	Turret->Rotate(Delta.Yaw);

	// Move the barrel the right amount this frame given a max speed and frame time


}


// Initialise aiming component
void UTankAimingComponent::InitialiseAimingComponent(UTankTurret * TurretToSet, UTankBarrel* BarrelToSet)
{
	if (!ensureAlways(TurretToSet && BarrelToSet)) return;
	Turret = TurretToSet;
  Barrel = BarrelToSet;
}

// Get firing status
EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
  return FiringStatus;
}

// Fire projectile from barrel 
void UTankAimingComponent::Fire()
{
  if (!ensureAlways(Barrel)) return;
  if (!ensureAlways(Projectile)) return;

  // Only fired within the firerate
  if (FiringStatus != EFiringStatus::Reloading)
  {
    FTransform SpawnActorTransform;
    SpawnActorTransform.SetComponents(
      Barrel->GetComponentQuat(),
      Barrel->GetSocketLocation(FName("EndBarrel")),
      FVector(1.f, 1.f, 1.f));

    // Spawn projectile
    AProjectile* LocalProjectile = GetWorld()->SpawnActor<AProjectile>(
      Projectile,
      SpawnActorTransform
      );


    // Activate projectile with launch speed
    LocalProjectile->Activate(LaunchSpeed);
    LastTimeFired = GetWorld()->GetTimeSeconds();

    FiringStatus = EFiringStatus::Reloading;
  }
}


