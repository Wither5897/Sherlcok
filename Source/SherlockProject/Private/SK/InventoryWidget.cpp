// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/InventoryWidget.h"
#include "SK/DescriptionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/MultiLineEditableText.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Engine/Engine.h"
#include "Jin/AJH_SummaryWidget.h"
#include "SK/MultiPlayerState.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DescriptionUI = Cast<UDescriptionWidget>(CreateWidget(GetWorld(), DescriptionUIFactory));
	DescriptionUI->AddToViewport(5);

	EvidenceList1->SetVisibility(ESlateVisibility::Visible);
	EvidenceList2->SetVisibility(ESlateVisibility::Hidden);
	EvidencePage->SetText(FText::FromString("1"));
	CaseGuessScreen->SetVisibility(ESlateVisibility::Hidden);

	SuspectTextField->SetVisibility(ESlateVisibility::Hidden);
	WeaponTextField->SetVisibility(ESlateVisibility::Hidden);
	MainEvidenceTextField->SetVisibility(ESlateVisibility::Hidden);
	SpecialThingTextField->SetVisibility(ESlateVisibility::Hidden);

	PageDownButton->OnClicked.AddDynamic(this, &UInventoryWidget::PageDownButtonClicked);
	PageUpButton->OnClicked.AddDynamic(this, &UInventoryWidget::PageUpButtonClicked);
	ShowEvidenceButton->OnClicked.AddDynamic(this, &UInventoryWidget::ShowEvidenceButtonClicked);
	ShowNoteButton->OnClicked.AddDynamic(this, &UInventoryWidget::ShowNoteButtonClicked);
	SuspectButton->OnClicked.AddDynamic(this, &UInventoryWidget::SuspectButtonClicked);
	WeaponButton->OnClicked.AddDynamic(this, &UInventoryWidget::WeaponButtonClicked);
	MainEvidenceButton->OnClicked.AddDynamic(this, &UInventoryWidget::MainEvidenceButtonClicked);
	SpecialThingButton->OnClicked.AddDynamic(this, &UInventoryWidget::SpecialThingButtonClicked);
	ResetButton->OnClicked.AddDynamic(this, &UInventoryWidget::ResetButtonClicked);

	InitTexture = nullptr;

	if ( check.Num() == 0 )
	{
		check.Init(false, 20);
	}

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if ( !me || !me->SummaryWidget) 
	{
		return;
	}
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

void UInventoryWidget::SuspectButtonClicked()
{
	DoubleClick(SuspectTextField);
	if ( !SavedTexture ) {
		return;
	}
	SuspectImage->SetBrushFromTexture(SavedTexture);
	auto* ps = me->GetPlayerState();
	me->ServerSetSummaryMulti(0, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::WeaponButtonClicked()
{
	DoubleClick(WeaponTextField);
	if ( !SavedTexture ) {
		return;
	}
	WeaponImage->SetBrushFromTexture(SavedTexture);
	auto* ps = me->GetPlayerState();
	me->ServerSetSummaryMulti(1, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::MainEvidenceButtonClicked()
{
	DoubleClick(MainEvidenceTextField);
	if ( !SavedTexture) {
		return;
	}
	MainEvidenceImage->SetBrushFromTexture(SavedTexture);
	auto* ps = me->GetPlayerState();
	me->ServerSetSummaryMulti(2, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::SpecialThingButtonClicked()
{
	DoubleClick(SpecialThingTextField);
	if ( !SavedTexture) {
		return;
	}
	SpecialThingImage->SetBrushFromTexture(SavedTexture);
	auto* ps = me->GetPlayerState();
	me->ServerSetSummaryMulti(3, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::ResetButtonClicked()
{
	SuspectImage->SetBrushFromTexture(InitTexture);
	WeaponImage->SetBrushFromTexture(InitTexture);
	MainEvidenceImage->SetBrushFromTexture(InitTexture);
	SpecialThingImage->SetBrushFromTexture(InitTexture);
}

void UInventoryWidget::InitDoubleClick()
{
	bIsDoubleClick = false;
}

void UInventoryWidget::DoubleClick(class UMultiLineEditableText* textbox)
{
	if ( bIsDoubleClick ) {
		bIsDoubleClick = false;
		textbox->SetVisibility(ESlateVisibility::Visible);
		textbox->SetKeyboardFocus();
		return;
	}
	bIsDoubleClick = true;
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UInventoryWidget::InitDoubleClick, 0.3f);
}
