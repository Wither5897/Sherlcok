// Fill out your copyright notice in the Description page of Project Settings.


#include "SherlockHUD.h"
#include "UW_Main.h"
#include "Widgets/SWidget.h"

ASherlockHUD::ASherlockHUD()
{
	static ConstructorHelpers::FClassFinder<UUW_Main> WBP_Main(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KHH/UI/WBP_Main.WBP_Main_C'"));
	
	if ( WBP_Main.Succeeded() )
	{
		MainUIClass = WBP_Main.Class;
	}
}

void ASherlockHUD::BeginPlay()
{
	Super::BeginPlay();

	CheckUIObject(); 

}

TSharedPtr<SWidget> ASherlockHUD::GetChatInputTextObject()
{
	return MainUIObject->GetChatInputTextObject();
}

void ASherlockHUD::AddChatMessage(const FString& Message)
{
	if ( !CheckUIObject() ) return;

	MainUIObject->AddChatMessage(Message);
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
			return true; 
		}
	}
	return false; 
}