// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"
#include "Engine/EngineBaseTypes.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetOwner()->GetActorLocation(); // Store the starting location of the owner	
	SetIsMovingUpwards(false); // Initialize the movement direction to downwards
	
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 

	FVector currentLocation = GetOwner()->GetActorLocation(); // Get the current location of the owner

	if (!(currentLocation.Equals(targetLocation))) // Only move if not already at the target location
	{
		float moveSpeed = distanceToMove.Length() / timeMoving; // Calculate the speed based on distance and time
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, moveSpeed); // Interpolate towards the target location at a constant speed
		GetOwner()->SetActorLocation(newLocation); // Set the new location of the owner
	}
}

bool UMover::GetIsMovingUpwards() { return isMovingUpwards; } // Getter for isMovingUpwards

void UMover::SetIsMovingUpwards(bool shouldMoveUpwards)  // Toggle the movement direction and update the target location
{ 
	isMovingUpwards = shouldMoveUpwards;
	targetLocation = isMovingUpwards ? startLocation + distanceToMove : startLocation; // Ternary operator to set the target location based on the movement direction
}

