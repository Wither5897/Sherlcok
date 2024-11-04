// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorToolWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UAJH_EditorToolWidget::NativeConstruct()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(0);
	// currentPageIndex = EditorWidgetSwitcher->GetActiveWidgetIndex();

	Main_Btn_Character->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Character);
	Main_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Character()
{
	currentPageIndex = EditorWidgetSwitcher->GetActiveWidgetIndex();
	PageHistory.Add(currentPageIndex);
	EditorWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Back()
{
	if ( PageHistory.Num() > 0 )
	{
		MemoriesPageIndex = PageHistory.Pop();
		EditorWidgetSwitcher->SetActiveWidgetIndex(MemoriesPageIndex);
	}
	else if ( Main_Btn_Back->IsPressed() )
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		EditorWidgetSwitcher->SetActiveWidgetIndex(0);
	}
}
