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



void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* OuterObject = UKismetSystemLibrary::GetOuterObject(this);
	Inven = Cast<UInventoryWidget>(UKismetSystemLibrary::GetOuterObject(OuterObject));
	if ( Inven ) {
		DescriptionUI = Inven->DescriptionUI;
		Inven->ItemArray.Add(this);
	}

	if ( GetMyNumber() <= 6 ) {
		Evidence->SetBrushFromTexture(ItemColor[GetMyNumber() - 1]);
	}
	Player1Light->SetVisibility(ESlateVisibility::Hidden);
	Player2Light->SetVisibility(ESlateVisibility::Hidden);
	Player3Light->SetVisibility(ESlateVisibility::Hidden);

	ItemButton->OnClicked.AddDynamic(this, &UItemWidget::ItemButtonClicked);

	//=======================================================================

	if ( check.Num() == 0 )
	{
		check.Init(false, 6);
	}

	notify = Cast<UUW_Notify>(CreateWidget(GetWorld(), NoticeUI));

	if ( notify )
	{
		notify->AddToViewport();
		notify->SetVisibility(ESlateVisibility::Hidden);
	}
	CheckConditions();
}

int32 UItemWidget::GetMyNumber()
{
	int32 value = UKismetStringLibrary::Conv_StringToInt(UKismetStringLibrary::GetSubstring(UKismetSystemLibrary::GetDisplayName(this), UKismetSystemLibrary::GetDisplayName(this).Len() - 2, 2));
	return value;
}

void UItemWidget::WhenFindItem(int32 PlayerID)
{
	QuestionMark->SetVisibility(ESlateVisibility::Hidden);

	int32 MyNumber = GetMyNumber();
	if ( MyNumber > 0 && MyNumber <= check.Num() )
	{
		check[MyNumber - 1] = true;
	}
	CheckConditions();

	switch (PlayerID)
	{
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

void UItemWidget::ItemButtonClicked()
{
	// WhenFindItem();
	if ( Inven->DescriptionUI ) {
		Inven->DescriptionUI->WhenItemClicked(GetMyNumber());
	}
}

//=======================================================================
//void UItemWidget::CheckConditions()
//{
//	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
//
//	if ( check[0] )
//	{
//		me->reportboard->CanvasPanel_138->SetVisibility(ESlateVisibility::Visible);
//		ShowNotifyWidget(1);
//
//	}
//	if ( check[1] )
//	{
//		ShowNotifyWidget(2);
//	}
//
//
//}

void UItemWidget::CheckConditions()
{
	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());

	if ( check[0] && check[1] && check[2] && check[3] && check[4] && check[5] ) // 목격자의 진술, 
	{
	   me->reportboard->CanvasPanel_138->SetVisibility(ESlateVisibility::Visible);
	   ShowNotifyWidget(1);
	}

	if ( check[0] && check[2] && check[4] )// 전문가의 견해 
	{
	   ShowNotifyWidget(2);
	}

	if ( check[2] && check[3] ) //  시체 검안서 
	{
		ShowNotifyWidget(3);
	}

	if ( check[2] ) //  잘린 손, 잘린 손 발견 신고 
	{
	   ShowNotifyWidget(4);
	}
}

void UItemWidget::ShowNotifyWidget(int32 value)
{
	if ( notify )
	{
		notify->notifySetting(value);
		notify->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UItemWidget::HideNotifyWidget, 5.0f, false);
	}
}

void UItemWidget::HideNotifyWidget()
{
	if ( notify )
	{
		notify->SetVisibility(ESlateVisibility::Hidden);
	}
}
