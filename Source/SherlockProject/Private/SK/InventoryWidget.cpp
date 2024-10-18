// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/InventoryWidget.h"
#include "SK/DescriptionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DescriptionUI = Cast<UDescriptionWidget>(CreateWidget(GetWorld(), DescriptionUIFactory));


	EvidenceList1->SetVisibility(ESlateVisibility::Visible);
	EvidenceList2->SetVisibility(ESlateVisibility::Hidden);
	EvidencePage->SetText(FText::FromString("1"));

	PageDownButton->OnClicked.AddDynamic(this, &UInventoryWidget::PageDownButtonClicked);
	PageUpButton->OnClicked.AddDynamic(this, &UInventoryWidget::PageUpButtonClicked);
}

void UInventoryWidget::PageDownButtonClicked()
{
	if ( EvidencePage->GetText().ToString() == "1" ) {
		return;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("hi")));
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("bye")));
		EvidenceList1->SetVisibility(ESlateVisibility::Hidden);
		EvidenceList2->SetVisibility(ESlateVisibility::Visible);
		EvidencePage->SetText(FText::FromString("2"));
	}
}

void UInventoryWidget::ShowEvidenceButtonClicked()
{
	
}

void UInventoryWidget::ShowNoteButtonClicked()
{
	
}
