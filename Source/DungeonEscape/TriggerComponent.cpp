// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (moveActor)
	{
		moverComponent = moveActor->FindComponentByClass<UMover>(); // Find the Mover component in the specified actor

		if (!moverComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find 'Mover' component."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MoveActor is null."));
	}

	if (isPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin); // Bind the overlap event
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd); // Bind the end overlap event
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}

/// <summary>
/// Sets the trigger state and updates the mover component accordingly.
/// </summary>
/// <param name="triggerState"></param>
void UTriggerComponent::SetTrigger(bool triggerState)
{
	isTriggerActivated = triggerState;
	
	if (moverComponent)
	{
		moverComponent->SetIsMovingUpwards(isTriggerActivated); // Set whether the door moves up or down based on the trigger's state
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s Mover component is null and therefore the trigger will not activate!"), *GetOwner()->GetActorNameOrLabel());
	}
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (moverComponent && OtherActor && OtherActor->ActorHasTag("PressurePlateActivator") && !isTriggerActivated)
	{
		SetTrigger(true); // Start moving upwards when overlap begins
	}
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (moverComponent && OtherActor && OtherActor->ActorHasTag("PressurePlateActivator") && isTriggerActivated)
	{
		SetTrigger(false); // Stop moving downwards when overlap ends	
	}
}

bool UTriggerComponent::GetIsTriggerActivated() { return isTriggerActivated; } // Returns whether the trigger is currently activated

UMover* UTriggerComponent::GetMoverComponent() { return moverComponent; } // Returns the reference to the Mover component

bool UTriggerComponent::GetIsPressurePlate() { return isPressurePlate; } // Returns whether this trigger acts as a pressure plate
