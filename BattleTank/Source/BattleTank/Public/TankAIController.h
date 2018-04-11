// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetAIMaterial(APawn* player, UMaterialInterface * Material_High, UMaterialInterface * Material_Low, UStaticMeshComponent* TankBody, UStaticMeshComponent* TankTurret, UStaticMeshComponent* TankBarrel, UStaticMeshComponent* LeftTankTrack, UStaticMeshComponent* RightTankTrack);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	bool IsAITank(APawn * player);

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnPossedTankDeath();
};
