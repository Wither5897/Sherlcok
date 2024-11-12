// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/CustomizingWidget.h"

#include "AJH_SherlockGameInstance.h"
#include "Components/Button.h"
#include "GameFramework/Character.h"
#include "SK/CustomizingCharacter.h"
#include "SK/MultiPlayerState.h"

void UCustomizingWidget::NativeConstruct(){
	Super::NativeConstruct();

	CoatLeftButton->OnClicked.AddDynamic(this, &UCustomizingWidget::CoatLeftButtonClicked);
	CoatRightButton->OnClicked.AddDynamic(this, &UCustomizingWidget::CoatRightButtonClicked);
	HatLeftButton->OnClicked.AddDynamic(this, &UCustomizingWidget::HatLeftButtonClicked);
	HatRightButton->OnClicked.AddDynamic(this, &UCustomizingWidget::HatRightButtonClicked);
	
	PlayButton->OnClicked.AddDynamic(this, &UCustomizingWidget::PlayButtonClicked);
	CoatIdx = 0;
	HatIdx = 0;

	me = Cast<ACustomizingCharacter>(GetOwningPlayer()->GetCharacter());
}

void UCustomizingWidget::CoatLeftButtonClicked(){
	if(CoatIdx < 0){
		return;
	}
	CoatIdx--;
	me->SetCoatMaterial(MaterialColor[CoatIdx]);
}

void UCustomizingWidget::CoatRightButtonClicked(){
	if(CoatIdx > 3){
		return;
	}
	CoatIdx++;
	me->SetCoatMaterial(MaterialColor[CoatIdx]);
}

void UCustomizingWidget::HatLeftButtonClicked(){
	if(HatIdx < 0){
		return;
	}
	HatIdx--;
	me->SetHatMaterial(MaterialColor[HatIdx]);
}

void UCustomizingWidget::HatRightButtonClicked(){
	if(HatIdx > 3){
		return;
	}
	HatIdx++;
	me->SetHatMaterial(MaterialColor[HatIdx]);
}

void UCustomizingWidget::PlayButtonClicked(){
	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	auto* ps = Cast<AMultiPlayerState>(GetOwningPlayer()->GetCharacter()->GetPlayerState());
	FCustomizingData newData;
	if(!ps){
		newData.PlayerIdNum = 0;
	}
	else{
		newData.PlayerIdNum = ps->GetPlayerIdNum();
	}
	newData.CoatIdx = CoatIdx;
	newData.HatIdx = HatIdx;

	gi->CustomizingDataArray.Add(newData);

	gi->FindMySession();
}
