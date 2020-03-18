// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
  
}

// Set barrel pointer
void ATank::SetBarrel(UTankBarrel* BarrelToSet)
{
  if (!ensureAlways(BarrelToSet)) return; 
  Barrel = BarrelToSet;
}

// Fire projectile from barrel 
void ATank::Fire()
{
	if (!ensureAlways(Barrel)) return;
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));

	// Only fired within the firerate
	if (GetWorld()->GetTimeSeconds() - LastTimeFired > 60.f / FireRate)
	{
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
		LocalProjectile->Activate(0);
		LastTimeFired = GetWorld()->GetTimeSeconds();
	}
}

