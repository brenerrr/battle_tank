// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
  Reloading, 
  Aiming, 
  Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

  UFUNCTION(BlueprintCallable, Category = "Input")
  void Fire();


  void AimAt(FVector& AimLocation);
	
  // Initialize aiming component
  UFUNCTION(BlueprintCallable, Category = Setup)
    void InitialiseAimingComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
		// Turn on debug helpers
		bool bDebug = true;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
    // Fire rate in rounds per minute
    float FireRate = 60.f;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
    // Projectile Launch Speed
    float LaunchSpeed = 3000.f;
	
	// Tank that owns this component 
	AActor* Tank = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringStatus FiringStatus = EFiringStatus::Aiming;


private:
  UPROPERTY(EditDefaultsOnly, Category = Setup)
    // Projectile type 
    TSubclassOf<AProjectile> Projectile;

  virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
  
  void UpdateFiringStatus();

  bool IsBarrelMoving();

  // Move the tank barrel towards aim direction
	void MoveBarrelTowards();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

  // Instant of last projectile fired
  float LastTimeFired = 0.f;

  FVector AimDirection = FVector(0);
  };
