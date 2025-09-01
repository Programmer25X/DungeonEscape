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

	keyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh")); // Creates the key mesh component
	keyMesh->SetupAttachment(rootComp); // Attach the key mesh component to the root component

	Tags.Add("Lock"); // Adds the "Lock" tag to the actor
}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

