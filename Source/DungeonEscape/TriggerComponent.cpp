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

	if (moveActor != nullptr)
	{
		mover = moveActor->FindComponentByClass<UMover>();

		if (mover != nullptr)
		{
			mover->isMoving = true;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to find 'Mover' component."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MoveActor is null."));
	}
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}
