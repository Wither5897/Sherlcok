// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ItemWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "SK/InventoryWidget.h"
#include "Components/Button.h"
#include "SK/DescriptionWidget.h"

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

	notify = Cast<UUW_Notify>(CreateWidget(GetWorld(), NoticeUI));

	if ( notify )
	{
		notify->AddToViewport();
		notify->SetVisibility(ESlateVisibility::Hidden);
	}
	// CheckConditions();
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
	if ( MyNumber > 0 && MyNumber <= Inven->check.Num() )
	{
		Inven->check[MyNumber - 1] = true;
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

void UItemWidget::CheckConditions()
{
	if ( Inven->check[0] && Inven->check[1] )
	{
		ShowNotifyWidget();
	}
}

void UItemWidget::ShowNotifyWidget()
{
	if ( notify )
	{
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
