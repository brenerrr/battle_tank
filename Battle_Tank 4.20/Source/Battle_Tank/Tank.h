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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector& AimLocation);

	UFUNCTION(BlueprintCallable)
		// Spawns a projectile from the end of the barrel
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTankAimingComponent* AimingComponent = nullptr;
	
	UFUNCTION(BlueprintCallable, Category = Setup)
		// Sets the barrel reference on the aiming component
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		// Sets the barrel reference on the aiming component
		void SetTurretlReference(UTankTurret* TurretToSet);
	
private: 
	// Tank barrel
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditAnywhere, Category = Firing)
		// Projectile Launch Speed
		float LaunchSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		// Projectile type 
		TSubclassOf<AProjectile> Projectile;


};
