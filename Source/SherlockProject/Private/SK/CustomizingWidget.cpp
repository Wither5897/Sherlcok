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
	CoatIdx--;
	if(CoatIdx < 0){
		CoatIdx = 0;
		return;
	}
	me->SetCoatMaterial(MaterialColor[CoatIdx]);
}

void UCustomizingWidget::CoatRightButtonClicked(){
	CoatIdx++;
	if(CoatIdx > 3){
		CoatIdx = 3;
		return;
	}
	me->SetCoatMaterial(MaterialColor[CoatIdx]);
}

void UCustomizingWidget::HatLeftButtonClicked(){
	HatIdx--;
	if(HatIdx < 0){
		HatIdx = 0;
		return;
	}
	me->SetHatMaterial(MaterialColor[HatIdx]);
}

void UCustomizingWidget::HatRightButtonClicked(){
	HatIdx++;
	if(HatIdx > 3){
		HatIdx = 3;
		return;
	}
	me->SetHatMaterial(MaterialColor[HatIdx]);
}

void UCustomizingWidget::PlayButtonClicked(){
	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	auto* ps = GetOwningPlayer()->GetPlayerState<AMultiPlayerState>();
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
