// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mover.h"
#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class DUNGEONESCAPE_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION() void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetTrigger(bool triggerState); // Function to set the trigger state

private:
	UMover* moverComponent; // Reference to the Mover component
	UPROPERTY(EditAnywhere) AActor* moveActor; // Actor that contains the Mover component
	UPROPERTY(EditAnywhere) bool isPressurePlate = false; // Whether this trigger acts as a pressure plate
	UPROPERTY(VisibleAnywhere) bool isTriggerActivated = false; // Whether the trigger is currently activated
	UPROPERTY(VisibleAnywhere) int32 numOfActivators = 0; // Number of activators currently overlapping the trigger
};
