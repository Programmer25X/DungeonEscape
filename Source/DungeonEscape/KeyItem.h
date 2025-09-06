// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyItem.generated.h"

UCLASS()
class DUNGEONESCAPE_API AKeyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKeyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString GetItemName(); // Getter for itemName

private:
	UPROPERTY(EditAnywhere) FString itemName; // Name of the collectable item
};
