// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector&);

	
	void SetBarrelReference(UStaticMeshComponent*);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Tank that owns this component 
	ATank* Tank = nullptr;


private:
	UStaticMeshComponent* Barrel;
	
};
