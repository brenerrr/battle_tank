// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	//void AimAt(FVector& AimLocation);

  // Set barrel pointer
  void SetBarrel(UTankBarrel* BarrelToSet); 

	UFUNCTION(BlueprintCallable)
		// Spawns a projectile from the end of the barrel
		void Fire();

  void AimAt(FVector& AimLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		// Fire rate in rounds per minute
		float FireRate = 60.f;



private: 
	// Tank barrel
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		// Projectile type 
		TSubclassOf<AProjectile> Projectile;
	
	// Instant of last projectile fired
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float LastTimeFired = 0.f;

  UTankAimingComponent* AimingComponent = nullptr; 

};
