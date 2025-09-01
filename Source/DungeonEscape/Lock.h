// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Lock.generated.h"

UCLASS()
class DUNGEONESCAPE_API ALock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere) USceneComponent* rootComp; // Root component
	UPROPERTY(VisibleAnywhere) UTriggerComponent* triggerComp; // Trigger component
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* keyItemMesh; // Key mesh component

	UPROPERTY(EditAnywhere) FString keyItemName; // Name of the lock
	UPROPERTY(VisibleAnywhere) bool isKeyItemPlaced = true; // Whether the key item is placed in the lock

public:
	bool GetIsKeyItemPlaced(); // Getter for isKeyItemPlaced
	void SetIsKeyItemPlaced(bool keyItemPlaced); // Setter for isKeyItemPlaced
};
