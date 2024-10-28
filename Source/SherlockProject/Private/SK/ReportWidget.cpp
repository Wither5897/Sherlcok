// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ReportWidget.h"

#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UReportWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CanvasPanel_19->SetVisibility(ESlateVisibility::Visible);
	CloseReportButton->OnClicked.AddDynamic(this, &UReportWidget::CloseReportButtonClicked);
}

void UReportWidget::CloseReportButtonClicked()
{
	CanvasPanel_19->SetVisibility(ESlateVisibility::Collapsed);
}

