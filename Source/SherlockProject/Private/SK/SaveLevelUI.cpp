// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/SaveLevelUI.h"

#include "AJH_SherlockGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void USaveLevelUI::NativeConstruct(){
	Super::NativeConstruct();

	ConfirmButton->OnClicked.AddDynamic(this, &USaveLevelUI::ConfirmButtonClicked);
}

void USaveLevelUI::ConfirmButtonClicked(){
	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	if(LevelNameEdit->GetText().IsEmpty()){
		return;
	}
	gi->SaveLevel(LevelNameEdit->GetText().ToString());
}
