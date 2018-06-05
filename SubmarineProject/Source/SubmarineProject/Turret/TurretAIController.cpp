// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretAIController.h"
#include "TurretAimingComponent.h"
#include "SubmarineProjectPawn.h"
#include "Engine/World.h"


void ATurretAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	//if (InPawn)
	//{
	//	auto PossessedTank = Cast<ASubmarineProjectPawn>(InPawn);
	//	if (!ensure(PossessedTank)) { return; }

	//	//Subscribe local method to the tanks death event
	//	PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);

	//}
}

void ATurretAIController::OnPossessedTankDeath()
{
	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}

// Called every frame
void ATurretAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerSub = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTurret = GetPawn();

	if (!ensure(PlayerSub && ControlledTurret)) { return; }

	// Move towards the player
	MoveToActor(PlayerSub, AcceptanceRadius); // TODO check radius is in cm

											   // Aim towards the player
	auto AimingComponent = ControlledTurret->FindComponentByClass<UTurretAimingComponent>();
	AimingComponent->AimAt(PlayerSub->GetActorLocation());

	if (AimingComponent->GetFiringState() == ETurretFiringState::Locked)
	{
		AimingComponent->Fire(); // TODO limit firing rate
	}
}
