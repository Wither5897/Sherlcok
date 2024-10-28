// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_SummaryWidget.h"
#include "Components/Button.h"
#include "SK/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "AJH_SherlockGameInstance.h"
#include "SK/MultiPlayerState.h"

void UAJH_SummaryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
	if ( !me ) {
		return;
	}
	InventoryUI = me->InventoryUI;

	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	FString PlayerName = gi->UserNickName;

	auto* ps = Cast<AMultiPlayerState>(me->GetPlayerState());
	if ( ps->GetPlayerId() == 0 ) {
		// Player1Name->SetText(FText::FromString(PlayerName));
	}
	else if ( ps->GetPlayerId() == 1 ) {
		// Player2Name->SetText(FText::FromString(PlayerName));
	}
	else if ( ps->GetPlayerId() == 2 ) {
		// Player3Name->SetText(FText::FromString(PlayerName));
	}

	if ( Btn_Submit )
	{
		Btn_Submit->OnClicked.AddDynamic(this, &UAJH_SummaryWidget::OnMyBtn_Click);
	}

}

void UAJH_SummaryWidget::OnMyBtn_Click()
{
	// 이미지를 이름을 지어주고 ex Player1Suspect, 헤더에서 바인딩 한다.
	// Player1Suspect
	//FSlateBrush suspectBrush = InventoryUI->SuspectImage->GetBrush();
	auto* ps = Cast<AMultiPlayerState>(me->GetPlayerState());
	/*if ( ps->GetPlayerId() == 0 ) {
		OnSuspectImage();
		OnWeaponImage();
		OnMainEvidenceImage();
		OnSpecialThingImage();
	}
	else if ( ps->GetPlayerId() == 1 ) {
		OnSuspectImage();
		OnWeaponImage();
		OnMainEvidenceImage();
		OnSpecialThingImage();
	}
	else if ( ps->GetPlayerId() == 2 ) {
		OnSuspectImage();
		OnWeaponImage();
		OnMainEvidenceImage();
		OnSpecialThingImage();
	}*/
	
}

void UAJH_SummaryWidget::OnSuspectImage(class UTexture2D* SavedTexture)
{
	//FSlateBrush suspectBrush = InventoryUI->SuspectImage->GetBrush();
	//Img_SuspectImage->SetBrushResourceObject(suspectBrush.GetResourceObject());
	if ( !Img_SuspectImage ) {
		return;
	}
	Img_SuspectImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnWeaponImage(class UTexture2D* SavedTexture)
{
	//FSlateBrush suspectBrush = InventoryUI->WeaponImage->GetBrush();
	//Img_WeaponImage->SetBrushResourceObject(suspectBrush.GetResourceObject());
	if ( !Img_WeaponImage ) {
		return;
	}
	Img_WeaponImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMainEvidenceImage(class UTexture2D* SavedTexture)
{
	//FSlateBrush suspectBrush = InventoryUI->MainEvidenceImage->GetBrush();
	//Img_MainEvidenceImage->SetBrushResourceObject(suspectBrush.GetResourceObject());
	if ( !Img_MainEvidenceImage ) {
		return;
	}
	Img_MainEvidenceImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnSpecialThingImage(class UTexture2D* SavedTexture)
{
	/*FSlateBrush suspectBrush = InventoryUI->SpecialThingImage->GetBrush();
	Img_SpecialThingImage->SetBrushResourceObject(suspectBrush.GetResourceObject());*/
	if ( !Img_SpecialThingImage ) {
		return;
	}
	Img_SpecialThingImage->SetBrushFromTexture(SavedTexture);
}
