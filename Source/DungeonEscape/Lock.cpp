// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")); // Creates the root component
	SetRootComponent(rootComp); // Sets the root component

	triggerComp = CreateDefaultSubobject<UTriggerComponent>(TEXT("Trigger Component")); // Creates the trigger component
	triggerComp->SetupAttachment(rootComp); // Attach the trigger component to the root component

	keyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh")); // Creates the key mesh component
	keyItemMesh->SetupAttachment(rootComp); // Attach the key mesh component to the root component

	Tags.Add("Lock"); // Adds the "Lock" tag to the actor
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	SetIsKeyItemPlaced(false); // Initialize the key item placement status to false
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

FString ALock::GetLockName() { return lockName; } // Getter for lockName	

/// <summary>
/// Returns whether the key item has been placed in the lock.
/// </summary>
/// <returns>True if the key item is placed; otherwise, false.</returns>
bool ALock::GetIsKeyItemPlaced() { return isKeyItemPlaced; } 

/// <summary>
/// Sets whether the key item has been placed in the lock and updates related components accordingly.
/// </summary>
/// <param name="keyItemPlaced">Indicates if the key item has been placed (true) or not (false).</param>
void ALock::SetIsKeyItemPlaced(bool keyItemPlaced) 
{ 
	isKeyItemPlaced = keyItemPlaced; 
	triggerComp->SetTrigger(keyItemPlaced); // Activate the trigger if the key item is not placed
	keyItemMesh->SetVisibility(keyItemPlaced); // Show or hide the key mesh based on whether the key item is placed
}

