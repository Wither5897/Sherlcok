// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AJH_SherlockGameInstance.h"

void UAJH_LoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CR_Btn_CreateRoom->OnClicked.AddDynamic(this, &UAJH_LoginWidget::CR_OnClickCreateRoom);
}

void UAJH_LoginWidget::CR_OnClickCreateRoom()
{
	// 방 이름
	FString roomName = CR_Edit_RoomName->GetText().ToString();
	// 최대 인원 수
	int32 playerCount = 3;

	// GameInstance 를 가져온다
	auto* gameInstance = Cast<UAJH_SherlockGameInstance>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		gameInstance->CreateMySession(roomName, playerCount); // 방 생성
	}

}
