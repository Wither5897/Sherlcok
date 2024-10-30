// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "SK/InventoryWidget.h"
#include "Components/Button.h"
#include "SK/DescriptionWidget.h"
#include "UW_ReportBoard.h"


void UItemWidget::NativeConstruct(){
	Super::NativeConstruct();

	auto* OuterObject = UKismetSystemLibrary::GetOuterObject(this);
	Inven = Cast<UInventoryWidget>(UKismetSystemLibrary::GetOuterObject(OuterObject));
	if (Inven){
		DescriptionUI = Inven->DescriptionUI;
		Inven->ItemArray.Add(this);
	}

	if (GetMyNumber() <= 9){
		Evidence->SetBrushFromTexture(ItemColor[GetMyNumber() - 1]);
	}
	Player1Light->SetVisibility(ESlateVisibility::Hidden);
	Player2Light->SetVisibility(ESlateVisibility::Hidden);
	Player3Light->SetVisibility(ESlateVisibility::Hidden);

	ItemButton->OnClicked.AddDynamic(this, &UItemWidget::ItemButtonClicked);

	//=======================================================================
	notify = Cast<UUW_Notify>(CreateWidget(GetWorld(), NoticeUI));

	if (notify){
		notify->AddToViewport();
		notify->SetVisibility(ESlateVisibility::Hidden);
	}
	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if (me->check.Num() == 0){
		me->check.Init(false, 9);
	}
}

int32 UItemWidget::GetMyNumber(){
	int32 value = UKismetStringLibrary::Conv_StringToInt(UKismetStringLibrary::GetSubstring(
		UKismetSystemLibrary::GetDisplayName(this), UKismetSystemLibrary::GetDisplayName(this).Len() - 2, 2));
	return value;
}

void UItemWidget::WhenFindItem(int32 PlayerID){
	QuestionMark->SetVisibility(ESlateVisibility::Hidden);

	int32 MyNumber = GetMyNumber();
	if (MyNumber > 0 && MyNumber <= me->check.Num()){
		me->check[MyNumber - 1] = true;
	}
	CheckConditions();

	switch (PlayerID){
	case 0:
		Player1Light->SetVisibility(ESlateVisibility::Visible);
		break;
	case 1:
		Player2Light->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2:
		Player3Light->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}
}

void UItemWidget::ItemButtonClicked(){
	// WhenFindItem();
	if (Inven->DescriptionUI){
		Inven->DescriptionUI->WhenItemClicked(GetMyNumber());
	}
}

//=======================================================================

void UItemWidget::CheckConditions(){

	if (!me->isNotify1Checked && me->check[3] && me->check[4] && me->check[5] && me->check[6] && me->check[7] && me->check[8]) // 목격자의 진술, 
	{
		me->reportboard->WitnessReport->SetVisibility(ESlateVisibility::Visible);
		ShowNotifyWidget(1);
		me->isNotify1Checked = true;
		return;
	}

	if (!me->isNotify2Checked && me->check[3] && me->check[5] && me->check[7]) // 전문가의 견해 
	{
		me->reportboard->ExpertReport->SetVisibility(ESlateVisibility::Visible);
		ShowNotifyWidget(2);
		me->isNotify2Checked = true;
		return;
	}

	if (!me->isNotify3Checked && me->check[5] && me->check[6]) //  시체 검안서 
	{
		me->reportboard->AutopsyReport->SetVisibility(ESlateVisibility::Visible);
		ShowNotifyWidget(3);
		me->isNotify3Checked = true;
		return;
	}

	if (!me->isNotify4Checked && me->check[5]) //  잘린 손, 잘린 손 발견 신고 
	{
		me->reportboard->HandReport->SetVisibility(ESlateVisibility::Visible);
		ShowNotifyWidget(4);
		me->isNotify4Checked = true;
		return;
	}
}

void UItemWidget::ShowNotifyWidget(int32 value){
	if (notify){
		notify->notifySetting(value);
		notify->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UItemWidget::HideNotifyWidget, 5.0f, false);

		notify->PlayNotifyAnim();
	}
}

void UItemWidget::HideNotifyWidget(){
	if (notify){
		notify->SetVisibility(ESlateVisibility::Hidden);
	}
}
