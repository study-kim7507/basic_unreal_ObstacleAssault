// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	FString MyString = "My String Value";
	FString MyName = this->GetName();
	
	UE_LOG(LogTemp, Display, TEXT("Here's My String : %s"), *MyString);
	UE_LOG(LogTemp, Display, TEXT("BeginPlay : %s"), *MyName);

	StartLocation = this->GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime) 
{
	// Reverse direction of motion if gone too far
	if (ShouldPlatformReturn()) 
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MovedDistance * MoveDirection;
		this->SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = this->GetActorLocation();
		CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		// Set the location
		this->SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// FRotator CurrentRotation = this->GetActorRotation();
	// CurrentRotation = CurrentRotation + RotationVelocity * DeltaTime;
	// this->SetActorRotation(CurrentRotation);
	this->AddActorLocalRotation(RotationVelocity * DeltaTime);
}

float AMovingPlatform::GetDistanceMoved() const 
{
	return FVector::Distance(StartLocation, this->GetActorLocation());
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	// Send Platform back if gone too far
		// Check how far we've moved
	return GetDistanceMoved() > MovedDistance;
}


