// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere) FVector distanceToMove; // Distance to move from the starting location
	UPROPERTY(EditAnywhere) float timeMoving = 4.0f; // Time in seconds to move to the target location
	UPROPERTY(VisibleAnywhere) bool isMovingUpwards = false; // Whether the owner is currently moving upwards
	FVector startLocation; // Starting location of the owner
	FVector targetLocation; // Target location to move to
		
public:
	bool GetIsMovingUpwards();
	void SetIsMovingUpwards(bool shouldMoveUpwards);
};
