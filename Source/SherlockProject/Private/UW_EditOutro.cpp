// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_EditOutro.h"

#include "Components/Button.h"
#include "Components/MultiLineEditableText.h"

void UUW_EditOutro::NativeConstruct(){
	Super::NativeConstruct();

	StorySave->OnClicked.AddDynamic(this, &UUW_EditOutro::StorySaveButtonClicked);
}

void UUW_EditOutro::StorySaveButtonClicked(){
	StoryText = EndingMessage->GetText();
	SetVisibility(ESlateVisibility::Hidden);
}
