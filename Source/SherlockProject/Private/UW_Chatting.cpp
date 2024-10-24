// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Chatting.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SherlockPlayerController.h"
#include "Components/Widget.h"

void UUW_Chatting::NativeConstruct()
{
	Super::NativeConstruct();
	if ( ChatInputBox )
	{
		ChatInputBox->OnTextCommitted.AddDynamic(this, &UUW_Chatting::OnChatTextCommitted);
	}
	ChatInputBox->SetIsEnabled(false);
}
void UUW_Chatting::AddChatMessage(const FString& Message)
{
	UTextBlock* NewTextBlock = NewObject<UTextBlock>(Chat_ScrollBox);
	NewTextBlock->SetText(FText::FromString(Message));

	FSlateFontInfo FontInfo = NewTextBlock->GetFont();
	FontInfo.Size = 15;
	NewTextBlock->SetFont(FontInfo);

	FSlateColor FontColor = FSlateColor(FLinearColor::Black);
	NewTextBlock->SetColorAndOpacity(FontColor);

	Chat_ScrollBox->AddChild(NewTextBlock);
	Chat_ScrollBox->ScrollToEnd();
}

void UUW_Chatting::SetChatInputTextMessage(const FText& Text)
{
	ChatInputBox->SetText(Text);
}

TSharedPtr<class SWidget> UUW_Chatting::GetChatInputTextObject()
{
	return ChatInputBox->GetCachedWidget();
}

void UUW_Chatting::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	ASherlockPlayerController* MyPC = Cast<ASherlockPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if ( MyPC == nullptr ) return;

	switch ( CommitMethod )
	{
	case ETextCommit::OnEnter:
		if ( Text.IsEmpty() == false )
		{
			MyPC->SendMessage(Text); // 메시지 보냄.
			SetChatInputTextMessage(FText::GetEmpty()); // 메세지 전송했으니, 비워줌.
		}
		//MyPC->FocusGame(); // 다시 게임으로 
		//break;
		MyPC->FocusChatInputText(); // 다시 채팅창으로 
		break;
	case ETextCommit::OnCleared:
		MyPC->FocusGame(); // 다시 게임으로 포커싱.
		break;
	}
}
