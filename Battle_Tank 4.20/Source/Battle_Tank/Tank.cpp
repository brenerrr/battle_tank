// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (BarrelToSet == nullptr) return;
	AimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;

}

void ATank::SetTurretlReference(UTankTurret * TurretToSet)
{
	if (TurretToSet == nullptr) return;
	AimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector& AimLocation)
{
	AimingComponent->AimAt(AimLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (Barrel == nullptr) return;
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	
	FTransform SpawnActorTransform;
	SpawnActorTransform.SetComponents(Barrel->GetComponentQuat(), 
									  Barrel->GetSocketLocation(FName("EndBarrel")), 
								      FVector(1.f, 1.f, 1.f));
	
	// Spawn projectile
	AProjectile* LocalProjectile = GetWorld()->SpawnActor<AProjectile>(
		Projectile,
		SpawnActorTransform
	);

	// Activate projectile with launch speed
	LocalProjectile->Activate(LaunchSpeed);

}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

