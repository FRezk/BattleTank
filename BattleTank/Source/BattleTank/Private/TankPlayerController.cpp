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

 bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation) const {
	 
	 FVector WorldDirection;
	 if (GetLookingDirection(WorldDirection))
	 {
		 GetLookVectorHitLocation(WorldDirection, out_HitLocation);
		 UE_LOG(LogTemp, Warning, TEXT("Aeww %s"), *out_HitLocation.ToString());
	 }
	 return true;
 }

 bool ATankPlayerController::GetLookingDirection(FVector& WorldDirection) const {
	 int32 ViewportSizeX, ViewportSizeY;
	 GetViewportSize(ViewportSizeX, ViewportSizeY); // Getting ViewportSizes
	 auto CrosshairLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	 
	 FVector discard; // will be discarded
	 return DeprojectScreenPositionToWorld(
		 CrosshairLocation.X,
		 CrosshairLocation.Y,
		 discard, WorldDirection);
 }

 bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDirection, FVector& out_HitLocation) const {
	 FHitResult HitResult; // Will be my Ray-Cast result
	 auto StartLocation = PlayerCameraManager->GetCameraLocation(); // Player Location, so i know where to start to cast
	 auto EndLocation = StartLocation + WorldDirection * LineTraceRange; // Will be discarded, but its the players rotation

	 if (GetWorld()->LineTraceSingleByChannel(
		 HitResult,
		 StartLocation,
		 EndLocation,
		 ECollisionChannel::ECC_Visibility
	 )) {
		 out_HitLocation = HitResult.Location;
		 return true;
	 }
	 out_HitLocation = FVector(0.0);
	 return false;
 }



  
