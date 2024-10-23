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

	if ( GetMyNumber() <= 6 ) {
		Evidence->SetBrushFromTexture(ItemColor[GetMyNumber() - 1]);
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
	if ( GetMyNumber() <= 6 ) {
		Inven->SavedTexture = ItemColor[GetMyNumber() - 1];
		// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("My Number: %d, Display Name: %s"), GetMyNumber() - 1, *UKismetSystemLibrary::GetDisplayName(Inven->SavedTexture)));
	}
}
