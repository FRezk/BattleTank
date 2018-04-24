// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h"

ATankAIController::ATankAIController() {
	//PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Tank not Possessed!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Possessing : %s"), *ControlledTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::AimTowardsPlayer() {
	if (!GetControlledTank()) { return; }

		FVector HitLocation = GetPlayerTank()->GetTargetLocation(); // The players location
		GetControlledTank()->AimAt(HitLocation);
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto FirstPlayerController = GetWorld()->GetFirstPlayerController();
	if (FirstPlayerController) {
		ATank* CastedFPC = Cast<ATank>(FirstPlayerController->GetPawn());
		if (CastedFPC) {
			return CastedFPC;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("First Player Controller found, but its not a tank!"));
			return nullptr;
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("First Player NOT FOUND!"));
		return nullptr;
	}
	
	
}
