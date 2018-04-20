// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "BattleTank.h"

#define OUT

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not possessing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

 ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

 void ATankPlayerController::AimTowardsCrosshair() {
	 if (!GetControlledTank()) { return; }
	 FVector HitLocation;
	 if (GetSightRayHitLocation(HitLocation)) {
		 //UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
	 }
 }

 bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {
	 OutHitLocation = FVector(1.0);
	 int32 ViewportSizeX, ViewportSizeY;
	 GetViewportSize(ViewportSizeX, ViewportSizeY);
	 auto CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	 UE_LOG(LogTemp, Warning, TEXT("Crosshair at: %s"), *CrosshairLocation.ToString());
	 return true;
 }


  
