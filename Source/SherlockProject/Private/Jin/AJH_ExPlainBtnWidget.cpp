// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_ExPlainBtnWidget.h"
#include "Components/Button.h"
#include "UW_EditorExplain.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorCharacter.h"
#include "GameFramework/PlayerController.h"

void UAJH_ExPlainBtnWidget::NativeConstruct()
{
	player = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	Btn_ExPlain->OnClicked.AddDynamic(this, &UAJH_ExPlainBtnWidget::OnMyBtn_ExPlain);
}

void UAJH_ExPlainBtnWidget::OnMyBtn_ExPlain()
{
	Btn_ExPlain->SetIsEnabled(false);
	// Btn_ExPlain->SetVisibility(ESlateVisibility::HitTestInvisible);
	//player->EditorExplain->SetVisibility(ESlateVisibility::Visible);
	player->CurrentWorldActor->EditorExplain->SetVisibility(ESlateVisibility::Visible);
	player->pc->SetInputMode(FInputModeUIOnly());
}

void UAJH_ExPlainBtnWidget::OnEnableBtn_ExPlain(bool bIsEnable)
{
	if ( bIsEnable )
	{
		Btn_ExPlain->SetIsEnabled(true);
	}
	else
	{
		Btn_ExPlain->SetIsEnabled(false);
	}
}
