// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ChatMessage.h"
#include "Components/EditableTextBox.h"


void UUW_ChatMessage::SetMessageText(const FText& MessageText, bool bIsSender)
{
	if ( bIsSender )
	{
		if ( sendMessage )
		{
			sendMessage->SetText(MessageText);
			sendMessage->SetVisibility(ESlateVisibility::Visible);
		}
		if ( getMessage )
		{
			getMessage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		if ( getMessage )
		{
			getMessage->SetText(MessageText);
			getMessage->SetVisibility(ESlateVisibility::Visible);
		}
		if ( sendMessage )
		{
			sendMessage->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
