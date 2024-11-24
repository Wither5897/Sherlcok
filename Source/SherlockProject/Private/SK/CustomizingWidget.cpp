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
	me->SetCoatMaterial(MaterialColor[CoatIdx]);
	me->SetHatMaterial(MaterialColor[HatIdx]);
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
	if(gi){
		FCustomizingData newData;
		newData.CoatIdx = CoatIdx;
		newData.HatIdx = HatIdx;
		if(me && me->LoadingUI){
			me->LoadingUI->SetVisibility(ESlateVisibility::Visible);
			CoatLeftButton->SetVisibility(ESlateVisibility::Hidden);
			CoatRightButton->SetVisibility(ESlateVisibility::Hidden);
			HatLeftButton->SetVisibility(ESlateVisibility::Hidden);
			HatRightButton->SetVisibility(ESlateVisibility::Hidden);
			PlayButton->SetVisibility(ESlateVisibility::Hidden);
		}
		gi->CustomizingDataArray.Add(newData);

		gi->FindMySession();
	}
}
