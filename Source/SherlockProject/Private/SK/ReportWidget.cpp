// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/ReportWidget.h"

#include "UW_ReportBoard.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UReportWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	CloseReportButton->OnClicked.AddDynamic(this, &UReportWidget::CloseReportButtonClicked);
	
	auto* OuterObject = UKismetSystemLibrary::GetOuterObject(this);
	OuterWidget = Cast<UUW_ReportBoard>(UKismetSystemLibrary::GetOuterObject(OuterObject));
	OuterWidget->Reports.Add(this);
}

void UReportWidget::CloseReportButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

