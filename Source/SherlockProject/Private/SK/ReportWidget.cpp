// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ReportWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UReportWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CloseReportButtonClicked();

	OpenReportButton->OnClicked.AddDynamic(this, &UReportWidget::OpenReportButtonClicked);
	CloseReportButton->OnClicked.AddDynamic(this, &UReportWidget::CloseReportButtonClicked);
}

void UReportWidget::OpenReportButtonClicked()
{
	WhenOnBoard->SetVisibility(ESlateVisibility::Hidden);
	WhenFocused->SetVisibility(ESlateVisibility::Visible);
}

void UReportWidget::CloseReportButtonClicked()
{
	WhenOnBoard->SetVisibility(ESlateVisibility::Visible);
	WhenFocused->SetVisibility(ESlateVisibility::Hidden);
}

