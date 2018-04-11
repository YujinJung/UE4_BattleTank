// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Delegate.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// TODO Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	bool isAimAt = AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked && isAimAt)
	{
		AimingComponent->Fire(ControlledTank);
	}
}

void ATankAIController::SetAIMaterial(APawn* player, UMaterialInterface * Material_High, UMaterialInterface * Material_Low, UStaticMeshComponent* TankBody, UStaticMeshComponent* TankTurret, UStaticMeshComponent* TankBarrel, UStaticMeshComponent* LeftTankTrack, UStaticMeshComponent* RightTankTrack)
{
	if (IsAITank(player))
	{
		TankBody->SetMaterial(0, Material_Low);
		TankTurret->SetMaterial(0, Material_Low);
		TankBarrel->SetMaterial(0, Material_High);
		LeftTankTrack->SetMaterial(0, Material_High);
		RightTankTrack->SetMaterial(0, Material_High);
	}
}

bool ATankAIController::IsAITank(APawn* player)
{
	if (GetWorld()->GetFirstPlayerController()->GetPawn() != player)
	{
		return true;
	}
	return false;
}