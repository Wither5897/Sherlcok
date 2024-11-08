// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_EditorToolWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Jin/AJH_EditorActor.h"
#include "Kismet/GameplayStatics.h"
#include "Jin/AJH_EditorCharacter.h"
#include "SK/SaveLevelUI.h"

void UAJH_EditorToolWidget::NativeConstruct()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(0);
	query = UEngineTypes::ConvertToTraceType(ECC_Visibility);
	pc = GetWorld()->GetFirstPlayerController();
	me = Cast<AAJH_EditorCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AAJH_EditorCharacter::StaticClass()));

	Main_Btn_Character->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Character);
	Main_Btn_Back->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyMain_Btn_Back);
	Btn_Character_1->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::OnMyBtn_Character_1);
	LevelSaveButton->OnClicked.AddDynamic(this, &UAJH_EditorToolWidget::LevelSaveButtonClicked);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Character()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(1);
}

void UAJH_EditorToolWidget::OnMyMain_Btn_Back()
{
	EditorWidgetSwitcher->SetActiveWidgetIndex(0);
}

void UAJH_EditorToolWidget::OnMyBtn_Character_1()
{
	//if ( !EditorActor || EditorActor == nullptr )
	//{
	//	// 새로운 액터 스폰
	//	pc->GetHitResultUnderCursorByChannel(query, true, outHit);
	//	FTransform transform(outHit.Location);
	//	EditorActor = GetWorld()->SpawnActor<AAJH_EditorActor>(EditorActorFactory, transform);
	//	EditorActor->bIsSpawn = true;
	//	me->bIsActorSpawn = true;
	//}
	//else
	//{
	//	EditorActor->bIsSpawn =false;
	//	me->bIsActorSpawn = false;
	//	EditorActor->Destroy();
	//	EditorActor = nullptr;
	//}
	/*if ( bIsSpawn == false )
	{
		me->OnMyEditorActorSpawn(true);
		bIsSpawn = true;
	}
	else
	{
		me->OnMyEditorActorSpawn(false);
		bIsSpawn = false;
	}*/
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true, 0);
	}
	else
	{
		me->OnMyEditorActorSpawn(false, 0);
	}
}

void UAJH_EditorToolWidget::OnMyBtn_Character_2()
{
	if ( me->bIsEditorActor == false )
	{
		me->OnMyEditorActorSpawn(true, 1);
	}
	else
	{
		me->OnMyEditorActorSpawn(false, 1);
	}
}

void UAJH_EditorToolWidget::LevelSaveButtonClicked(){
	me->SaveLevelWidget->SetVisibility(ESlateVisibility::Visible);
}
