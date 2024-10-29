// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ReportBoard.h"
#include "SK/ItemWidget.h"


void UUW_ReportBoard::NativeConstruct()
{
	Super::NativeConstruct();

	WidgetSwitcher_1->SetActiveWidgetIndex(0);
	BackgroundBlur_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Hidden);

	FirstReport->SetVisibility(ESlateVisibility::Visible);
	HandReport->SetVisibility(ESlateVisibility::Hidden);
	WitnessReport->SetVisibility(ESlateVisibility::Hidden);
	ExpertReport->SetVisibility(ESlateVisibility::Hidden);
	AutopsyReport->SetVisibility(ESlateVisibility::Hidden);


	CloseButton->OnClicked.AddDynamic(this, &UUW_ReportBoard::CloseButtonClicked);
	OpenReportB->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence);
	OpenReportB1->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence1);
	OpenReportB2->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence2);
	OpenReportB3->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence3);
	OpenReportB4->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence4);
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

void UUW_ReportBoard::OpenEvidence4()
{
	WidgetSwitcher_1->SetVisibility(ESlateVisibility::Visible);
	WidgetSwitcher_1->SetActiveWidgetIndex(4);
}

void UUW_ReportBoard::CloseButtonClicked()
{
	BackgroundBlur_1->SetVisibility(ESlateVisibility::Hidden);
}


