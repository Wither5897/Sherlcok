// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ReportBoard.h"
#include "SK/ItemWidget.h"


void UUW_ReportBoard::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetSwitcher_1->SetActiveWidgetIndex(0);
	BackgroundBlur_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Hidden);

	CanvasPanel_1->SetVisibility(ESlateVisibility::Visible);
	CanvasPanel_138->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_2->SetVisibility(ESlateVisibility::Hidden);
	CanvasPanel_3->SetVisibility(ESlateVisibility::Hidden);


	CloseButton->OnClicked.AddDynamic(this, &UUW_ReportBoard::CloseButtonClicked);
	OpenReportButton->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence);
	OpenReportButton_1->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence1);
	OpenReportButton_2->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence2);
	OpenReportButton_3->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence3);
}

void UUW_ReportBoard::OpenEvidence()
{
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetActiveWidgetIndex(0);
}

void UUW_ReportBoard::OpenEvidence1()
{
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetActiveWidgetIndex(1);
}

void UUW_ReportBoard::OpenEvidence2()
{
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetActiveWidgetIndex(2);
}

void UUW_ReportBoard::OpenEvidence3()
{
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetActiveWidgetIndex(3);
}



void UUW_ReportBoard::CloseButtonClicked()
{
	BackgroundBlur_1->SetVisibility(ESlateVisibility::Hidden);
}


