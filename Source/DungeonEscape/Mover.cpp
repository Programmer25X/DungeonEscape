// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

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
	UE_LOG(LogTemp, Warning, TEXT("My owner is %s and my location is %s"), *GetOwner()->GetActorNameOrLabel(), *startLocation.ToCompactString()); // Log the name of the owner
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector currentLocation = GetOwner()->GetActorLocation(); // Get the current location of the owner
	currentLocation.Z += (100.0f * DeltaTime); // Move the owner up at 100 units per second
	GetOwner()->SetActorLocation(currentLocation); // Set the new location of the owner
}

