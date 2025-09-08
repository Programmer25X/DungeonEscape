// Fill out your copyright notice in the Description page of Project Settings.


#include "HiddenCollectable.h"

// Sets default values
AHiddenCollectable::AHiddenCollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("CollectableItem");
}

// Called when the game starts or when spawned
void AHiddenCollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHiddenCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AHiddenCollectable::GetCollectableName()
{
	return collectableItemName;
}

