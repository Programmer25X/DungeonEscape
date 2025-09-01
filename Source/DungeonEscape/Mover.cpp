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
		if (timeMoving != 0.0f)
		{
			float moveSpeed = distanceToMove.Length() / abs(timeMoving); // Calculate the speed to move based on distance and time
			FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, moveSpeed); // Interpolate towards the target location at a constant speed
			GetOwner()->SetActorLocation(newLocation); // Set the new location of the owner
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("timeMoving is set to 0. You cannot divide by 0.")); // Log a warning if timeMoving is zero to avoid division by zero
		}
	}
}

/// <summary>
/// Returns whether the mover is currently moving upwards.
/// </summary>
/// <returns>True if the mover is moving upwards; otherwise, false.</returns>
bool UMover::GetIsMovingUpwards() { return isMovingUpwards; } // Getter for isMovingUpwards

/// <summary>
/// Sets whether the mover is moving upwards and updates the target location accordingly.
/// </summary>
/// <param name="shouldMoveUpwards">Indicates if the mover should move upwards (true) or not (false).</param>
void UMover::SetIsMovingUpwards(bool shouldMoveUpwards) 
{ 
	isMovingUpwards = shouldMoveUpwards;
	targetLocation = isMovingUpwards ? startLocation + distanceToMove : startLocation; // Ternary operator to set the target location based on the movement direction
}

