// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Chatting.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_Chatting : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void AddChatMessage(const FString& Message);
	void SetChatInputTextMessage(const FText& Text);

	TSharedPtr<class SWidget> GetChatInputTextObject();

	UPROPERTY(Meta = (BindWidget))
	class UScrollBox* Chat_ScrollBox;

	UPROPERTY(Meta = (BindWidget))
	class UEditableTextBox* ChatInputBox;

	UFUNCTION()
	void OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

    
};
