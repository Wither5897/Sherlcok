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

	BackgroundBlur_96->SetVisibility(ESlateVisibility::Hidden);

	CloseButton->OnClicked.AddDynamic(this, &UUW_ReportBoard::CloseButtonClicked);
	OpenReportB->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence);
	OpenReportB1->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence1);
	OpenReportB2->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence2);
	OpenReportB3->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence3);
	OpenReportB4->OnClicked.AddDynamic(this, &UUW_ReportBoard::OpenEvidence4);
}

void UUW_ReportBoard::OpenEvidence() // 1. 시체검안서
{
	Reports[0]->SetVisibility(ESlateVisibility::Visible);
	BackgroundBlur_96-> SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence1() // 2. 손 짤림
{
	Reports[1]->SetVisibility(ESlateVisibility::Visible);
	BackgroundBlur_96->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence2() // 3. 목격자
{
	Reports[2]->SetVisibility(ESlateVisibility::Visible);
	BackgroundBlur_96->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence3() // 4. 전문가
{
	Reports[3]->SetVisibility(ESlateVisibility::Visible);
	BackgroundBlur_96->SetVisibility(ESlateVisibility::Visible);
}

void UUW_ReportBoard::OpenEvidence4() // 5. 시체 검안서
{
	Reports[4]->SetVisibility(ESlateVisibility::Visible);
	BackgroundBlur_96->SetVisibility(ESlateVisibility::Visible);
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


