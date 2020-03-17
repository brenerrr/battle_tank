// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt(FVector& AimLocation, float LaunchSpeed)
{
	if (Barrel == nullptr) return;

	// Calculate toss direction to hit aimlocation with launchspeed
	FVector TossDirection(0);
	TArray<AActor*> ActorsToIgnore;	ActorsToIgnore.Add(Tank);

	bool bIsShotValid = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		TossDirection,
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

	// Debug perfect shot trajectory
	if (bIsShotValid)
	{
		MoveBarrelTowards(TossDirection);

		if (bDebug)
		{
			DrawDebugDirectionalArrow(
				GetWorld(),
				Barrel->GetSocketLocation(FName("EndBarrel")),
				TossDirection.GetSafeNormal()*100.f + Barrel->GetSocketLocation(FName("EndBarrel")),
				10.f,
				FColor::Blue,
				false,
				-1.f,
				0,
				10.f);
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection)
{

	// Compute the difference between current barrel direction and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation() ;
	FRotator AimRotator = AimDirection.Rotation();

	FRotator Delta = AimRotator - BarrelRotator;

	Barrel->Elevate(Delta.Pitch);
	Turret->Rotate(Delta.Yaw);

	// Move the barrel the right amount this frame given a max speed and frame time


}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(GetOwner());
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (BarrelToSet == nullptr) return;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (TurretToSet == nullptr) return;
	Turret = TurretToSet;
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

