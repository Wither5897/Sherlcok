// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/InventoryWidget.h"
#include "SK/DescriptionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DescriptionUI = Cast<UDescriptionWidget>(CreateWidget(GetWorld(), DescriptionUIFactory));
	DescriptionUI->AddToViewport(5);

	EvidenceList1->SetVisibility(ESlateVisibility::Visible);
	EvidenceList2->SetVisibility(ESlateVisibility::Hidden);
	EvidencePage->SetText(FText::FromString("1"));
	CaseGuessScreen->SetVisibility(ESlateVisibility::Hidden);

	PageDownButton->OnClicked.AddDynamic(this, &UInventoryWidget::PageDownButtonClicked);
	PageUpButton->OnClicked.AddDynamic(this, &UInventoryWidget::PageUpButtonClicked);
	ShowEvidenceButton->OnClicked.AddDynamic(this, &UInventoryWidget::ShowEvidenceButtonClicked);
	ShowNoteButton->OnClicked.AddDynamic(this, &UInventoryWidget::ShowNoteButtonClicked);
}

void UInventoryWidget::PageDownButtonClicked()
{
	if ( EvidencePage->GetText().ToString() == "1" ) {
		return;
	}
	else {
		EvidenceList1->SetVisibility(ESlateVisibility::Visible);
		EvidenceList2->SetVisibility(ESlateVisibility::Hidden);
		EvidencePage->SetText(FText::FromString("1"));
	}
}

void UInventoryWidget::PageUpButtonClicked()
{
	if ( EvidencePage->GetText().ToString() == "2" ) {
		return;
	}
	else {
		EvidenceList1->SetVisibility(ESlateVisibility::Hidden);
		EvidenceList2->SetVisibility(ESlateVisibility::Visible);
		EvidencePage->SetText(FText::FromString("2"));
	}
}

void UInventoryWidget::ShowEvidenceButtonClicked()
{	
	if ( CaseRecordScreen->IsVisible() ) {
		return;
	}
	CaseRecordScreen->SetVisibility(ESlateVisibility::Visible);
	CaseGuessScreen->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::ShowNoteButtonClicked()
{
	if ( CaseGuessScreen->IsVisible() ) {
		return;
	}
	CaseGuessScreen->SetVisibility(ESlateVisibility::Visible);
	CaseRecordScreen->SetVisibility(ESlateVisibility::Hidden);
}
