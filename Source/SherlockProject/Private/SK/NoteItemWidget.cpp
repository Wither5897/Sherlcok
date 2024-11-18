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
		Inven->NoteItemArray.Add(this);
	}

	if ( GetMyNumber() <= 9 ) {
		Evidence->SetBrushFromTexture(ItemColor[GetMyNumber() - 1]);
		SavedTexture = ItemColor[GetMyNumber() - 1];
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
	QuestionMark->SetColorAndOpacity(FLinearColor(0.01f, 0.01f, 0.01f, 0.75f));
	QuestionMark->SetBrushFromTexture(nullptr);
}

void UNoteItemWidget::ItemButtonClicked()
{
	if ( GetMyNumber() <= 9 ) {
		Inven->SavedTexture = ItemColor[GetMyNumber() - 1];
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("My Number: %d, Display Name: %s"), GetMyNumber() - 1, *UKismetSystemLibrary::GetDisplayName(Inven->SavedTexture)));
	}
}

void UNoteItemWidget::DisableInteraction(){
	QuestionMark->SetVisibility(ESlateVisibility::Visible);
	ItemButton->SetIsEnabled(false);
	bIsDisabled = true;
}

void UNoteItemWidget::EnableInteraction(){
	FLinearColor Color = QuestionMark->GetColorAndOpacity();
	if (Color == FLinearColor(0.01f, 0.01f, 0.01f, 0.75f)){
		QuestionMark->SetVisibility(ESlateVisibility::Hidden);
		ItemButton->SetIsEnabled(true);
		bIsDisabled = false;
	}
}