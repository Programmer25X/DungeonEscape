// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyWidget_PlayerHUD.generated.h"

class UCanvasPanel; 
class UTextBlock; 

/**
 * 
 */
UCLASS()
class DUNGEONESCAPE_API UMyWidget_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true")) UCanvasPanel* mainCanvas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true")) UTextBlock* notificationText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = "true")) UTextBlock* numberCollectedText; 

public: 

	void SetNotificationText(FString collectableName);
	void SetCollectablesCollected(unsigned int numCollected);
	void ClearNotificationText();

};
