// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonEscapeCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "KeyItem.h"
#include "Lock.h"
#include "HiddenCollectable.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MyWidget_PlayerHUD.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DungeonEscape.h"

ADungeonEscapeCharacter::ADungeonEscapeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void ADungeonEscapeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADungeonEscapeCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ADungeonEscapeCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADungeonEscapeCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADungeonEscapeCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADungeonEscapeCharacter::LookInput);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADungeonEscapeCharacter::Interact);
	}
	else
	{
		UE_LOG(LogDungeonEscape, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADungeonEscapeCharacter::Interact()
{
	FVector startLocation = FirstPersonCameraComponent->GetComponentLocation(); // Gets the camera location
	FVector endLocation = startLocation + (FirstPersonCameraComponent->GetForwardVector() * interactDistance); // Gets the forward vector and multiplies it by the interact distance
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Green, false, 5.0f); // Draws a debug line to visualise the raycast.

	FCollisionShape interactionSphere = FCollisionShape::MakeSphere(interactSphereRadius); // Creates a sphere for the raycast to pass into the trace function.
	DrawDebugSphere(GetWorld(), endLocation, interactSphereRadius, 12, FColor::Green, false, 5.0f); // Draws a debug sphere to visualise the raycast.

	FHitResult hitResult; // Variable to store hit result data.
	bool isHittingObject = GetWorld()->SweepSingleByChannel(hitResult, startLocation, endLocation, FQuat::Identity, ECC_GameTraceChannel2, interactionSphere); // Performs the sweep (sphere trace) using the defined parameters.
	
	if (isHittingObject)
	{
		AActor* hitActor = hitResult.GetActor(); // Gets the actor that was hit.	

		if(hitActor->ActorHasTag("KeyItem")) // Checks if the hit actor has the "Collectible" tag.
		{
			AKeyItem* keyItem = Cast<AKeyItem>(hitActor);

			if(keyItem)
			{
				playerInventory.Add(keyItem->GetKeyName()); // Adds the item to the player's inventory.
				UE_LOG(LogTemp, Display, TEXT("You have found key: %s"), *keyItem->GetKeyName()); // Logs the name of the collected item.
				keyItem->Destroy(); // Destroys the item in the world.
			}
		}
		else if (hitActor->ActorHasTag("Lock"))
		{
			ALock* lock = Cast<ALock>(hitActor);
			if (lock)
			{
				if (playerInventory.Contains(lock->GetLockName()) && !lock->GetIsKeyItemPlaced()) // If the player has the key item and it is not already placed in the lock
				{ 
					lock->SetIsKeyItemPlaced(true); // Place the key item in the lock
					playerInventory.Remove(lock->GetLockName()); // Remove the key item from the player's inventory
					UE_LOG(LogTemp, Display, TEXT("You have unlocked the passage!")); // Logs that the lock has been unlocked.
				}
				else if (!playerInventory.Contains(lock->GetLockName()) && lock->GetIsKeyItemPlaced())
				{
					playerInventory.Add(lock->GetLockName()); // Add the key item back to the player's inventory
					lock->SetIsKeyItemPlaced(false); // Remove the key item from the lock
				}
			}
		}
		else if (hitActor->ActorHasTag("CollectableItem"))
		{
			AHiddenCollectable* hiddenCollectable = Cast<AHiddenCollectable>(hitActor);
			if (hiddenCollectable)
			{
				UE_LOG(LogTemp, Display, TEXT("You have found a hidden collectable: %s"), *hiddenCollectable->GetCollectableName());
				if (!playerHUD)
				{
					TArray<UUserWidget*> foundWidgets;
					UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), foundWidgets, UMyWidget_PlayerHUD::StaticClass(), false);

					if (foundWidgets.Num() > 0)
					{
						playerHUD = Cast<UMyWidget_PlayerHUD>(foundWidgets[0]);
					}
				}

				if (playerHUD)
				{
					playerHUD->SetNotificationText(hiddenCollectable->GetCollectableName());
				}

				hiddenCollectable->Destroy();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("You are not interacting with anything")); // Logs that nothing was hit.
	}
}

void ADungeonEscapeCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ADungeonEscapeCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ADungeonEscapeCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ADungeonEscapeCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ADungeonEscapeCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ADungeonEscapeCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}
