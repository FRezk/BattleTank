// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Testando Begin Play"));

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

 ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}



