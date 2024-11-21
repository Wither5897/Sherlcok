// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_EditIntro.h"

#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/MultiLineEditableText.h"

void UUW_EditIntro::NativeConstruct(){
	Super::NativeConstruct();

	TitleSave->OnClicked.AddDynamic(this, &UUW_EditIntro::TitleSaveButtonClicked);
}

void UUW_EditIntro::TitleSaveButtonClicked(){
	TitleText = TitleEditText->GetText();
	SubTitleText = SubTitleTextMulti->GetText();
	SetVisibility(ESlateVisibility::Hidden);
}
