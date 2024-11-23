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
#include "Board.h"
#include "Kismet/GameplayStatics.h"



void UItemWidget::NativeConstruct() {
	Super::NativeConstruct();

	auto* OuterObject = UKismetSystemLibrary::GetOuterObject(this);
	Inven = Cast<UInventoryWidget>(UKismetSystemLibrary::GetOuterObject(OuterObject));
	if ( Inven ) {
		DescriptionUI = Inven->DescriptionUI;
		Inven->ItemArray.Add(this);
	}
	
	FWidgetTransform NewTransform;
	NewTransform.Angle = FMath::RandRange(-10, 10);
	SetRenderTransform(NewTransform);

	if ( GetMyNumber() <= 9 ) {
		Evidence->SetBrushFromTexture(ItemColor[GetMyNumber() - 1]);
	}
	Player1Light->SetVisibility(ESlateVisibility::Hidden);
	Player2Light->SetVisibility(ESlateVisibility::Hidden);
	Player3Light->SetVisibility(ESlateVisibility::Hidden);

	ItemButton->OnClicked.AddDynamic(this, &UItemWidget::ItemButtonClicked);

	//=======================================================================

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if ( me && me->check.Num() == 0 ) {
		me->check.Init(false, 9);
	}
}

int32 UItemWidget::GetMyNumber() {
	int32 value = UKismetStringLibrary::Conv_StringToInt(UKismetStringLibrary::GetSubstring(
		UKismetSystemLibrary::GetDisplayName(this), UKismetSystemLibrary::GetDisplayName(this).Len() - 2, 2));
	return value;
}

void UItemWidget::WhenFindItem(int32 PlayerID)
{
	QuestionMark->SetVisibility(ESlateVisibility::Hidden);

	switch ( PlayerID ) {
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

void UItemWidget::VisibleBoard()
{
	int32 MyNumber = GetMyNumber();

	if ( MyNumber > 0 && MyNumber <= me->check.Num() )
	{
		me->check[MyNumber - 1] = true;
		// me->PlayEvidenceSound();
	}
	me->reportboard->CheckCondition(); // UI
	me->Board->reportboard->CheckCondition(); // board
}

void UItemWidget::ItemButtonClicked() {
	// WhenFindItem();
	if ( Inven->DescriptionUI ) {
		Inven->DescriptionUI->WhenItemClicked(GetMyNumber());
	}
}


