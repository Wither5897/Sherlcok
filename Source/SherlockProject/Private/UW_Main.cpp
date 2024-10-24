// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Main.h"
#include "UW_Chatting.h"
#include "Components/Widget.h"

TSharedPtr<class SWidget> UUW_Main::GetChatInputTextObject()
{
	return UW_Chatting->GetChatInputTextObject();
}

void UUW_Main::AddChatMessage(const FString& Message)
{
	UW_Chatting->AddChatMessage(Message);
}
