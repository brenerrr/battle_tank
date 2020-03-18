// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track allows movement of the tank 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	// Sets throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);


protected:
	virtual void BeginPlay() override;
  
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
  UTankTrack();

  void CorrectSidewaysSlipping(float DeltaTime);
	// Force applied on tank at maximum throttle
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MaxTrackForce = 400000.f;
	
	// Root component of tank
	UPrimitiveComponent* TankBody = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Debug)
	bool bDebug = false;

};
