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
  Locked,
  OutOfAmmo
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
  // Initialize aiming component
  UFUNCTION(BlueprintCallable, Category = Setup)
    void InitialiseAimingComponent(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet);

  UFUNCTION(BlueprintCallable, Category = "Getter")
  EFiringStatus GetFiringStatus() const;

  UFUNCTION(BlueprintCallable, Category = "Getter")
  int GetAmmoCount() const; 

  UFUNCTION(BlueprintCallable, Category = "Input")
  void Fire();

	// Sets default values for this component's properties
	UTankAimingComponent();

  void AimAt(FVector& AimLocation);
	
protected:

  UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup")
    // Projectile type 
    TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
		// Turn on debug helpers
		bool bDebug = false;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
    // Fire rate in rounds per minute
    float FireRate = 60.f;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
    // Projectile Launch Speed
    float LaunchSpeed = 3000.f;

  UPROPERTY(EditDefaultsOnly, Category = Firing)
    // Projectile Launch Speed
    int Ammo = 5;

	virtual void BeginPlay() override;
	
	// Tank that owns this component 
	AActor* Tank = nullptr;

  UPROPERTY(BlueprintReadOnly, Category = "State")
  EFiringStatus FiringStatus = EFiringStatus::Aiming;


private:
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
