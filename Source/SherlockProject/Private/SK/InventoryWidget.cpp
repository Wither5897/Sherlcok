// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/InventoryWidget.h"
#include "SK/DescriptionWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/MultiLineEditableText.h"
#include "Components/Image.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Engine/Engine.h"
#include "Jin/AJH_SummaryWidget.h"
#include "SK/MultiPlayerState.h"
#include "SK/NoteItemWidget.h"

void UInventoryWidget::NativeConstruct(){
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
	CompleteButton->OnClicked.AddDynamic(this, &UInventoryWidget::CompleteButtonClicked);

	InitTexture = nullptr;

	if (check.Num() == 0){
		check.Init(false, 20);
	}

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if (!me || !me->SummaryWidget){
		return;
	}
}

void UInventoryWidget::PageDownButtonClicked(){
	if (EvidencePage->GetText().ToString() == "1"){
		return;
	}
	else{
		EvidenceList1->SetVisibility(ESlateVisibility::Visible);
		EvidenceList2->SetVisibility(ESlateVisibility::Hidden);
		EvidencePage->SetText(FText::FromString("1"));

		me->PlayPaperSound();
	}
}

void UInventoryWidget::PageUpButtonClicked(){
	if (EvidencePage->GetText().ToString() == "2"){
		return;
	}
	else{
		EvidenceList1->SetVisibility(ESlateVisibility::Hidden);
		EvidenceList2->SetVisibility(ESlateVisibility::Visible);
		EvidencePage->SetText(FText::FromString("2"));

		me->PlayPaperSound();
	}
}

void UInventoryWidget::ShowEvidenceButtonClicked(){
	if (CaseRecordScreen->IsVisible()){
		return;
	}
	FWidgetTransform NewTransform;
	NewTransform.Angle = 90;
	NewTransform.Translation = FVector2D(20, 0);
	ShowEvidenceButton->SetRenderTransform(NewTransform);
	EvidenceButtonBackground->SetRenderTransform(NewTransform);

	NewTransform.Translation = FVector2D(-20, 0);
	ShowNoteButton->SetRenderTransform(NewTransform);
	NoteButtonBackground->SetRenderTransform(NewTransform);

	CaseRecordScreen->SetVisibility(ESlateVisibility::Visible);
	CaseGuessScreen->SetVisibility(ESlateVisibility::Hidden);

	me->PlayPaperSound();
}

void UInventoryWidget::ShowNoteButtonClicked(){
	if (CaseGuessScreen->IsVisible()){
		return;
	}
	FWidgetTransform NewTransform;
	NewTransform.Angle = 90;
	NewTransform.Translation = FVector2D(20, 0);
	ShowNoteButton->SetRenderTransform(NewTransform);
	NoteButtonBackground->SetRenderTransform(NewTransform);

	NewTransform.Translation = FVector2D(-20, 0);
	ShowEvidenceButton->SetRenderTransform(NewTransform);
	EvidenceButtonBackground->SetRenderTransform(NewTransform);

	CaseGuessScreen->SetVisibility(ESlateVisibility::Visible);
	CaseRecordScreen->SetVisibility(ESlateVisibility::Hidden);

	me->PlayPaperSound();
}

void UInventoryWidget::SuspectButtonClicked(){
	auto* ps = me->GetPlayerState();
	DoubleClick(SuspectTextField);
	if (!SavedTexture){
		for (UNoteItemWidget* NoteItem : NoteItemArray){
			if (NoteItem && NoteItem->SavedTexture == SuspectImage->GetBrush().GetResourceObject()) {
				RestoreNoteItemInteraction(NoteItem);
			}
		}
		SuspectImage->SetBrushFromTexture(InitTexture);
		me->ServerSetSummaryMulti(0, InitTexture, ps->GetPlayerId());
		return;
	}
	SuspectImage->SetBrushFromTexture(SavedTexture);
	for (UNoteItemWidget* NoteItem : NoteItemArray){
		if (NoteItem && NoteItem->SavedTexture == SavedTexture && !NoteItem->IsDisabled()){
			NoteItem->DisableInteraction();
		}
		else if (NoteItem && NoteItem->IsDisabled() &&
			NoteItem->SavedTexture != WeaponImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != MainEvidenceImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != SpecialThingImage->GetBrush().GetResourceObject()){
			RestoreNoteItemInteraction(NoteItem);
		}
	}

	me->ServerSetSummaryMulti(0, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::WeaponButtonClicked(){
	auto* ps = me->GetPlayerState();
	DoubleClick(WeaponTextField);
	if (!SavedTexture){
		for (UNoteItemWidget* NoteItem : NoteItemArray){
			if (NoteItem && NoteItem->SavedTexture == WeaponImage->GetBrush().GetResourceObject()) {
				RestoreNoteItemInteraction(NoteItem);
			}
		}
		WeaponImage->SetBrushFromTexture(InitTexture);
		me->ServerSetSummaryMulti(1, InitTexture, ps->GetPlayerId());
		return;
	}
	WeaponImage->SetBrushFromTexture(SavedTexture);
	for (UNoteItemWidget* NoteItem : NoteItemArray){
		if (NoteItem && NoteItem->SavedTexture == SavedTexture && !NoteItem->IsDisabled()){
			NoteItem->DisableInteraction();
		}
		else if (NoteItem && NoteItem->IsDisabled() &&
			NoteItem->SavedTexture != SuspectImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != MainEvidenceImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != SpecialThingImage->GetBrush().GetResourceObject()){
			RestoreNoteItemInteraction(NoteItem);
		}
	}
	me->ServerSetSummaryMulti(1, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::MainEvidenceButtonClicked(){
	auto* ps = me->GetPlayerState();
	DoubleClick(MainEvidenceTextField);
	if (!SavedTexture){
		for (UNoteItemWidget* NoteItem : NoteItemArray){
			if (NoteItem && NoteItem->SavedTexture == MainEvidenceImage->GetBrush().GetResourceObject()) {
				RestoreNoteItemInteraction(NoteItem);
			}
		}
		MainEvidenceImage->SetBrushFromTexture(InitTexture);
		me->ServerSetSummaryMulti(2, InitTexture, ps->GetPlayerId());
		return;
	}

	MainEvidenceImage->SetBrushFromTexture(SavedTexture);
	for (UNoteItemWidget* NoteItem : NoteItemArray){
		if (NoteItem && NoteItem->SavedTexture == SavedTexture && !NoteItem->IsDisabled()){
			NoteItem->DisableInteraction();
		}
		else if (NoteItem && NoteItem->IsDisabled() &&
			NoteItem->SavedTexture != WeaponImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != SuspectImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != SpecialThingImage->GetBrush().GetResourceObject()){
			RestoreNoteItemInteraction(NoteItem);
		}
	}
	me->ServerSetSummaryMulti(2, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::SpecialThingButtonClicked(){
	auto* ps = me->GetPlayerState();
	DoubleClick(SpecialThingTextField);
	if (!SavedTexture){
		for (UNoteItemWidget* NoteItem : NoteItemArray){
			if (NoteItem && NoteItem->SavedTexture == SpecialThingImage->GetBrush().GetResourceObject()) {
				RestoreNoteItemInteraction(NoteItem);
			}
		}
		SpecialThingImage->SetBrushFromTexture(InitTexture);
		me->ServerSetSummaryMulti(3, InitTexture, ps->GetPlayerId());
		return;
	}
	SpecialThingImage->SetBrushFromTexture(SavedTexture);
	for (UNoteItemWidget* NoteItem : NoteItemArray){
		if (NoteItem && NoteItem->SavedTexture == SavedTexture && !NoteItem->IsDisabled()){
			NoteItem->DisableInteraction();
		}
		else if (NoteItem && NoteItem->IsDisabled() &&
			NoteItem->SavedTexture != WeaponImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != MainEvidenceImage->GetBrush().GetResourceObject() &&
			NoteItem->SavedTexture != SuspectImage->GetBrush().GetResourceObject()){
			RestoreNoteItemInteraction(NoteItem);
		}
	}
	me->ServerSetSummaryMulti(3, SavedTexture, ps->GetPlayerId());
	SavedTexture = nullptr;
}

void UInventoryWidget::ResetButtonClicked(){
	SuspectImage->SetBrushFromTexture(InitTexture);
	WeaponImage->SetBrushFromTexture(InitTexture);
	MainEvidenceImage->SetBrushFromTexture(InitTexture);
	SpecialThingImage->SetBrushFromTexture(InitTexture);

	for (UNoteItemWidget* NoteItem : NoteItemArray){
		RestoreNoteItemInteraction(NoteItem);
	}

	auto* ps = me->GetPlayerState();
	if (ps->GetPlayerId() == 0){
		me->SummaryWidget->Img_SuspectImage1->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_WeaponImage1->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_MainEvidenceImage1->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_SpecialThingImage1->SetBrushFromTexture(InitTexture);
	}
	else if (ps->GetPlayerId() == 1){
		me->SummaryWidget->Img_SuspectImage2->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_WeaponImage2->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_MainEvidenceImage2->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_SpecialThingImage2->SetBrushFromTexture(InitTexture);
	}
	else{
		me->SummaryWidget->Img_SuspectImage3->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_WeaponImage3->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_MainEvidenceImage3->SetBrushFromTexture(InitTexture);
		me->SummaryWidget->Img_SpecialThingImage3->SetBrushFromTexture(InitTexture);
	}
}

void UInventoryWidget::CompleteButtonClicked(){
	SetVisibility(ESlateVisibility::Hidden);
	me->SummaryWidget->SetVisibility(ESlateVisibility::Visible);
}

void UInventoryWidget::InitDoubleClick(){
	bIsDoubleClick = false;
}

void UInventoryWidget::DoubleClick(class UMultiLineEditableText* textbox){
	if (bIsDoubleClick){
		bIsDoubleClick = false;
		textbox->SetVisibility(ESlateVisibility::Visible);
		textbox->SetKeyboardFocus();
		return;
	}
	bIsDoubleClick = true;
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UInventoryWidget::InitDoubleClick, 0.3f);
}

void UInventoryWidget::RestoreNoteItemInteraction(UNoteItemWidget* NoteItem){
	if (NoteItem && NoteItem->IsDisabled()){
		NoteItem->EnableInteraction();
	}
}
