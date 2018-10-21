// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector& AimLocation)
{
	if (Barrel == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s. Barrel location: %s"), *Tank->GetName(), *AimLocation.ToString(),
		*Barrel->GetComponentLocation().ToString());
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(GetOwner());

}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

