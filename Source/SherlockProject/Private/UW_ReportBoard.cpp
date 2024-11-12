// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_ReportBoard.h"

#include "SherlockPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "SK/AnimPawn.h"
#include "SK/InventoryWidget.h"
#include "SK/ItemWidget.h"
#include "SK/MultiPlayerState.h"
#include "SK/NoteItemWidget.h"


void UUW_ReportBoard::NativeConstruct(){
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

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	ps = Cast<AMultiPlayerState>(me->GetPlayerState());
	
}

void UUW_ReportBoard::OpenEvidence() // 1. 시체검안서
{
	Reports[0]->SetVisibility(ESlateVisibility::Visible);
	BackgroundBlur_96->SetVisibility(ESlateVisibility::Visible);


	//me->InventoryUI->ItemArray[0]->WhenFindItem(ps->GetPlayerId());
	//me->InventoryUI->NoteItemArray[0]->WhenFindItem();
	//me->InventoryUI->ItemArray[1]->WhenFindItem(ps->GetPlayerId());
	//me->InventoryUI->NoteItemArray[1]->WhenFindItem();
	//me->InventoryUI->ItemArray[2]->WhenFindItem(ps->GetPlayerId());
	//me->InventoryUI->NoteItemArray[2]->WhenFindItem();

	if (me && me->InventoryUI && ps){
		if (me->InventoryUI->ItemArray.IsValidIndex(0) && me->InventoryUI->ItemArray[0]){
			me->InventoryUI->ItemArray[0]->WhenFindItem(ps->GetPlayerIdNum());
		}

		if (me->InventoryUI->NoteItemArray.IsValidIndex(0) && me->InventoryUI->NoteItemArray[0]){
			me->InventoryUI->NoteItemArray[0]->WhenFindItem();
		}

		if (me->InventoryUI->ItemArray.IsValidIndex(1) && me->InventoryUI->ItemArray[1]){
			me->InventoryUI->ItemArray[1]->WhenFindItem(ps->GetPlayerIdNum());
		}

		if (me->InventoryUI->NoteItemArray.IsValidIndex(1) && me->InventoryUI->NoteItemArray[1]){
			me->InventoryUI->NoteItemArray[1]->WhenFindItem();
		}

		if (me->InventoryUI->ItemArray.IsValidIndex(2) && me->InventoryUI->ItemArray[2]){
			me->InventoryUI->ItemArray[2]->WhenFindItem(ps->GetPlayerIdNum());
		}

		if (me->InventoryUI->NoteItemArray.IsValidIndex(2) && me->InventoryUI->NoteItemArray[2]){
			me->InventoryUI->NoteItemArray[2]->WhenFindItem();
		}
	}
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

void UUW_ReportBoard::CloseButtonClicked(){
	SetVisibility(ESlateVisibility::Hidden);
	auto* pc = Cast<ASherlockPlayerController>(GetOwningPlayer());
	pc->SetInputMode(FInputModeGameOnly());
	pc->SetShowMouseCursor(false);

	me->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UUW_ReportBoard::CheckCondition(){
	if (me->check[5] && !bHandReport) // 잘린 손, 잘린 손 발견 신고
	{
		ShowNotifyWidget(4);
		HandReport->SetVisibility(ESlateVisibility::Visible);
		bHandReport = true;
	}

	if (me->check[5] && me->check[6] && !bAutopsyReport) // 시체 검안서
	{
		ShowNotifyWidget(3);
		AutopsyReport->SetVisibility(ESlateVisibility::Visible);
		bAutopsyReport = true;
	}

	if (me->check[3] && me->check[5] && me->check[7] && !bExpertReport) // 전문가의 견해
	{
		ShowNotifyWidget(2);
		ExpertReport->SetVisibility(ESlateVisibility::Visible);
		bExpertReport = true;
	}

	if (me->check[3] && me->check[4] && me->check[5] && me->check[6] && me->check[7] && me->check[8] && !bWitnessReport)
	// 목격자의 진술
	{
		ShowNotifyWidget(1);
		WitnessReport->SetVisibility(ESlateVisibility::Visible);
		bWitnessReport = true;
	}
	if (me->check[3] && me->check[5] && me->check[8] && !bSequence){
		FMovieSceneSequencePlaybackSettings PlaybackSettings;
		ALevelSequenceActor* OutActor;
		ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(), LevelSequence, PlaybackSettings, OutActor);
		if (LevelSequencePlayer){
			AnimPawn = Cast<AAnimPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), AAnimPawn::StaticClass()));
			AnimPawn->SetActorHiddenInGame(false);
			LevelSequencePlayer->OnFinished.AddDynamic(this, &UUW_ReportBoard::SetAnimPawnVisibility);
			LevelSequencePlayer->Play();
		}
		bSequence = true;
	}
}


void UUW_ReportBoard::ShowNotifyWidget(int32 value){
	if (me->Notify){
		me->Notify->notifySetting(value);
		me->Notify->SetVisibility(ESlateVisibility::Visible);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUW_ReportBoard::HideNotifyWidget, 5.0f, false);

		me->Notify->PlayNotifyAnim();
	}
}

void UUW_ReportBoard::HideNotifyWidget(){
	if (me->Notify){
		me->Notify->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UUW_ReportBoard::SetAnimPawnVisibility(){
	AnimPawn->SetActorHiddenInGame(true);
}
