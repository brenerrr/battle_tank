// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
  Reloading, 
  Aiming, 
  Locked
};

class ATank;
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector& AimLocation);
	
  // Initialize aiming component
  UFUNCTION(BlueprintCallable, Category = Setup)
    void InitialiseAimingComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		// Turn on debug helpers
		bool bDebug = true;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Tank that owns this component 
	ATank* Tank = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringStatus FiringStatus = EFiringStatus::Aiming;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
    // Projectile Launch Speed
    float LaunchSpeed = 3000.f;

private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;

  // Move the tank barrel towards aim direction
	void MoveBarrelTowards(const FVector& AimDirection);
  };
