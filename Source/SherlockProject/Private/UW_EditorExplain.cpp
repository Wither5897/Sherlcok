// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_EditorExplain.h"
#include "Components/Button.h"
#include "Jin/AJH_ExPlainBtnWidget.h"
#include "Jin/AJH_EditorCharacter.h"
#include "Jin/AJH_WorldActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MultiLineEditableText.h"

void UUW_EditorExplain::NativeConstruct()
{
	player = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	ExplainDelete->OnClicked.AddDynamic(this, &UUW_EditorExplain::OnMyExplainDelete);
	ExplainSave->OnClicked.AddDynamic(this, &UUW_EditorExplain::OnMyExplainSave);
}

void UUW_EditorExplain::OnMyExplainSave()
{
	player->CurrentWorldActor->ExplainText = ExplainMultiEditText->GetText().ToString();
}

void UUW_EditorExplain::OnMyExplainDelete()
{
	SetVisibility(ESlateVisibility::Collapsed);
	// player->ExPlainBtnWidget->Btn_ExPlain->SetIsEnabled(false);
	player->CurrentWorldActor->ExPlainBtnWidget->OnEnableBtn_ExPlain(true);
	player->CurrentWorldActor->ExPlainBtnWidget->Btn_ExPlain->SetVisibility(ESlateVisibility::Visible);
	player->pc->SetInputMode(FInputModeGameAndUI());
}
