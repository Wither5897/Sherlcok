// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Chatting.h"
#include "Widgets/SWidget.h"
#include "UW_Main.generated.h"

/**
 * 
 */
UCLASS()
class SHERLOCKPROJECT_API UUW_Main : public UUserWidget
{
	GENERATED_BODY()
	
public:
	TSharedPtr<class SWidget> GetChatInputTextObject();
	void AddChatMessage(const FString& Message);

	UPROPERTY(Meta = (BindWidget))
	class UUW_Chatting* WBP_Chat;
};
