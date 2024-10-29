// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_SummaryWidget.h"

#include <string>

#include "Components/Button.h"
#include "SK/InventoryWidget.h"
#include "Kismet/GameplayStatics.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "AJH_SherlockGameInstance.h"
#include "Engine/Engine.h"
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

void UAJH_SummaryWidget::OnSuspectImage(class UTexture2D* SavedTexture)
{
	if ( !Img_SuspectImage ) {
		return;
	}
	Img_SuspectImage->SetBrushFromTexture(SavedTexture);
	
}

void UAJH_SummaryWidget::OnWeaponImage(class UTexture2D* SavedTexture)
{
	if ( !Img_WeaponImage ) {
		return;
	}
	Img_WeaponImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMainEvidenceImage(class UTexture2D* SavedTexture)
{
	if ( !Img_MainEvidenceImage ) {
		return;
	}
	Img_MainEvidenceImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnSpecialThingImage(class UTexture2D* SavedTexture)
{
	if ( !Img_SpecialThingImage ) {
		return;
	}
	Img_SpecialThingImage->SetBrushFromTexture(SavedTexture);
}

void UAJH_SummaryWidget::OnMyBtn_Click(){
	// for (int32 i = 0; i < AllTexture.Num(); i++){
	// 	if (AllTexture[i] && Img_SuspectImage->Brush.GetResourceObject() == AllTexture[i]){
	// 		ModifyDataTable("Suspect", FString::Printf("Clue" + FString::FromInt(i)));
	// 	}
	// 	if (AllTexture[i] && Img_WeaponImage->Brush.GetResourceObject() == AllTexture[i]){
	// 		ModifyDataTable("Weapon", FString::Printf("Clue" + FString::FromInt(i)));
	// 	}
	// 	if (AllTexture[i] && Img_MainEvidenceImage->Brush.GetResourceObject() == AllTexture[i]){
	// 		ModifyDataTable("MainEvidence", FString::Printf("Clue" + FString::FromInt(i)));
	// 	}
	// 	if (AllTexture[i] && Img_SpecialThingImage->Brush.GetResourceObject() == AllTexture[i]){
	// 		ModifyDataTable("SpecialThing", FString::Printf("Clue" + FString::FromInt(i)));
	// 	}
	// }
}