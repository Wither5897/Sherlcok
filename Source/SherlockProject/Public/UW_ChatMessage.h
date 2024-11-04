// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "UW_ChatMessage.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_ChatMessage : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetMessageText(const FText& MessageText, bool bIsSender);

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* getMessage;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* sendMessage;
};
