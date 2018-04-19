// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("AI Tank not Possessed!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Possessing : %s"), *ControlledTank->GetName());
	}
	GetPlayerTank();
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::GetPlayerTank() const
{
	auto FirstPlayerController = GetWorld()->GetFirstPlayerController();
	if (FirstPlayerController) {
		auto CastedFPC = Cast<ATank>(FirstPlayerController->GetPawn());
		if (CastedFPC) {
			UE_LOG(LogTemp, Warning, TEXT("Found the player tank! Its %s"), *CastedFPC->GetName());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("First Player Controller found, but its not a tank!"));
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("First Player NOT FOUND!"));
	}
	
	
}
