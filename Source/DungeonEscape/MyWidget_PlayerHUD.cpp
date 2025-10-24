// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWidget_PlayerHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"


void UMyWidget_PlayerHUD::SetNotificationText(FString collectableName)
{
	if (notificationText)
	{
		FTimerHandle waitTimerHandle;
		notificationText->SetText(FText::FromString(FString::Printf(TEXT("Collected: %s"), *collectableName))); // Displays that the player found a collectable
		GetWorld()->GetTimerManager().SetTimer(waitTimerHandle, this, &UMyWidget_PlayerHUD::ClearNotificationText, 5.0f, false); // Clears the notification after 5 seconds

	}
}

/// <summary>
/// Sets the text for the number of collectables found.
/// </summary>
/// <param name="numCollected"></param>
void UMyWidget_PlayerHUD::SetCollectablesCollected(unsigned int numCollected)
{
	if (numberCollectedText)
	{
		numberCollectedText->SetText(FText::FromString(FString::Printf(TEXT("Collectables Found: %d/4"), numCollected))); // Updates the number of collectables found
	}
}

/// <summary>
/// Clears the notification text after a delay.
/// </summary>

void UMyWidget_PlayerHUD::ClearNotificationText()
{
	if (notificationText)
	{ 
		notificationText->SetText(FText::GetEmpty()); // Clears the notification text from the HUD
	}
}
