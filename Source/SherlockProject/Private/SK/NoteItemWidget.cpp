// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/NoteItemWidget.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SK/InventoryWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Kismet/KismetStringLibrary.h"

void UNoteItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* OuterObject = UKismetSystemLibrary::GetOuterObject(this);
	Inven = Cast<UInventoryWidget>(UKismetSystemLibrary::GetOuterObject(OuterObject));
	if ( Inven ) {
		DescriptionUI = Inven->DescriptionUI;
	}

	if ( GetMyNumber() >= 1 ) {
		Evidence->SetColorAndOpacity(ItemColor[( GetMyNumber() - 1 ) % 8]);
	}

	ItemButton->OnClicked.AddDynamic(this, &UNoteItemWidget::ItemButtonClicked);
}

int32 UNoteItemWidget::GetMyNumber()
{
	int32 value = UKismetStringLibrary::Conv_StringToInt(UKismetStringLibrary::GetSubstring(UKismetSystemLibrary::GetDisplayName(this), UKismetSystemLibrary::GetDisplayName(this).Len() - 2, 2));
	return value;
}

void UNoteItemWidget::WhenFindItem()
{
	QuestionMark->SetVisibility(ESlateVisibility::Hidden);
}

void UNoteItemWidget::ItemButtonClicked()
{
	Inven->SavedTexture = ItemColor[( GetMyNumber() - 1 ) % 8];
}
