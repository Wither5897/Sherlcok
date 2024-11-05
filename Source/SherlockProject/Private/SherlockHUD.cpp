// Fill out your copyright notice in the Description page of Project Settings.
#include "SherlockHUD.h"
#include "UW_Main.h"
#include "Widgets/SWidget.h"
#include "UW_ChatMessage.h"
#include "UW_Chatting.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

ASherlockHUD::ASherlockHUD()
{
	static ConstructorHelpers::FClassFinder<UUW_Main> WBP_Main(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/Chat/WBP_Main.WBP_Main_C'"));
	
	if ( WBP_Main.Succeeded() )
	{
		MainUIClass = WBP_Main.Class;
	}

	static ConstructorHelpers::FClassFinder<UUW_Chatting> WBP_Chat(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/Chat/WBP_Chat.WBP_Chat_C'"));
	if ( WBP_Chat.Succeeded() )
	{
		ChatUIClass = WBP_Chat.Class;
	}

	static ConstructorHelpers::FClassFinder<UUW_ChatMessage> WBP_ChatMessage(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/Chat/WBP_ChatMesssage.WBP_ChatMesssage_C'"));
	if ( WBP_ChatMessage.Succeeded() )
	{
		ChatMessageClass = WBP_ChatMessage.Class;
	}

}

void ASherlockHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); 

	// 알림(느낌표) 표시
	if ( MainUIObject && MainUIObject->ChatNotificationText )
	{
		MainUIObject->ChatNotificationText->SetVisibility(ESlateVisibility::Hidden);
	}

}

TSharedPtr<SWidget> ASherlockHUD::GetChatInputTextObject()
{
	return ChatUIObject ? ChatUIObject->GetChatInputTextObject() : nullptr;
}

void ASherlockHUD::AddChatMessage(const FString& Message, bool bIsSender)
{
	if ( !CheckUIObject() || !ChatUIObject ) return;

	UUW_ChatMessage* ChatMessageWidget = CreateWidget<UUW_ChatMessage>(GetOwningPlayerController(), ChatMessageClass);
	if ( ChatMessageWidget )
	{
		ChatMessageWidget->SetMessageText(FText::FromString(Message), bIsSender);
		if ( ChatUIObject->Chat_ScrollBox )
		{
			ChatUIObject->Chat_ScrollBox->AddChild(ChatMessageWidget);
			ChatUIObject->Chat_ScrollBox->ScrollToEnd(); // 스크롤 끝으로 
		}
	}
}

bool ASherlockHUD::CheckUIObject()
{
	if ( MainUIObject == nullptr ) // UI가 없다면 생성.
	{
		return CreateUIObject();
	}
	return true; 
}

bool ASherlockHUD::CreateUIObject()
{
	if ( MainUIClass )
	{
		MainUIObject = CreateWidget<UUW_Main>(GetOwningPlayerController(), MainUIClass);
		if ( MainUIObject )
		{
			MainUIObject->AddToViewport();

			ChatUIObject = MainUIObject->WBP_Chat;
			if ( ChatUIObject )
			{
				return true;
			}
		}
	}
	return false; 
}