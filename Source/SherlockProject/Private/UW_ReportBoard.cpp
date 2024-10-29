// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ReportBoard.h"

#include "SherlockPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SK/ItemWidget.h"


void UUW_ReportBoard::NativeConstruct()
{
	Super::NativeConstruct();

	BackgroundBlur_1->SetVisibility(ESlateVisibility::Visible);

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
	Reports[0]->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence1()
{
	Reports[1]->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence2()
{
	Reports[2]->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence3()
{
	Reports[3]->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence4()
{
	Reports[4]->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::CloseButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	auto* pc = Cast<ASherlockPlayerController>(GetOwningPlayer());
	pc->SetInputMode(FInputModeGameOnly());
	pc->SetShowMouseCursor(false);

	auto* me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}


