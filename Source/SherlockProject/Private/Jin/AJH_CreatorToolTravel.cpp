// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_CreatorToolTravel.h"
#include "Components/Button.h"
#include "SherlockPlayerController.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UAJH_CreatorToolTravel::NativeConstruct()
{
	Btn_Travel->OnClicked.AddDynamic(this, &UAJH_CreatorToolTravel::OnMyBtn_Travel);
	Btn_Cancel->OnClicked.AddDynamic(this, &UAJH_CreatorToolTravel::OnMyBtn_Cancel);
}

void UAJH_CreatorToolTravel::OnMyBtn_Travel()
{
	if (pc->IsLocalController() && player)
	{
		pc->ClientTravel(FString("/Game/Jin/Maps/EditorToolDevelopMap."), ETravelType::TRAVEL_Absolute);
	}
	
}

void UAJH_CreatorToolTravel::OnMyBtn_Cancel()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
