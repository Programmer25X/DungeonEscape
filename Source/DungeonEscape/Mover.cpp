// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
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
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); 


	if (isMoving)
	{	
		targetLocation = startLocation + distanceToMove;
	}
	else
	{
		targetLocation = startLocation;
	}

	FVector currentLocation = GetOwner()->GetActorLocation(); // Get the current location of the owner

	if (!(currentLocation.Equals(targetLocation)))
	{
		float moveSpeed = distanceToMove.Length() / timeMoving;
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, moveSpeed);
		GetOwner()->SetActorLocation(newLocation); // Set the new location of the owner
	}
}

