// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/SaveLevelUI.h"

#include "AJH_SherlockGameInstance.h"
#include "UW_EditIntro.h"
#include "UW_EditOutro.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Jin/AJH_EditorToolWidget.h"
#include "Jin/AJH_LightWidget.h"
#include "Jin/AJH_Sun.h"

void USaveLevelUI::NativeConstruct(){
	Super::NativeConstruct();

	me = Cast<AAJH_EditorCharacter>(GetOwningPlayer()->GetCharacter());
	
	SetVisibility(ESlateVisibility::Hidden);
	
	ConfirmButton->OnClicked.AddDynamic(this, &USaveLevelUI::ConfirmButtonClicked);
	CloseButton->OnClicked.AddDynamic(this, &USaveLevelUI::CloseButtonClicked);
}

void USaveLevelUI::ConfirmButtonClicked(){
	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	if(LevelNameEdit->GetText().IsEmpty()){
		return;
	}
	gi->SaveLevel(LevelNameEdit->GetText().ToString(), me->EditorWidget->SaveIntroUI->TitleText, me->EditorWidget->SaveIntroUI->SubTitleText, me->EditorWidget->SaveOutroUI->StoryText, me->LightWidget->HeightSun->height_Sun);
	SetVisibility(ESlateVisibility::Hidden);
}

void USaveLevelUI::CloseButtonClicked(){
	FText text = FText::FromString("");
	LevelNameEdit->SetText(text);
	SetVisibility(ESlateVisibility::Hidden);
}
