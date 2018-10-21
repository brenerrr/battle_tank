// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CheckForValidPointer.h"
#include "Tank.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector& AimLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UTankAimingComponent* AimingComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
	
private: 
	UStaticMeshComponent* Barrel = nullptr;
	
	
	
};
