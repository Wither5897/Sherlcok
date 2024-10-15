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
	// �� �̸�
	FString roomName = CR_Edit_RoomName->GetText().ToString();
	// �ִ� �ο� ��
	int32 playerCount = 3;

	// GameInstance �� �����´�
	auto* gameInstance = Cast<UAJH_SherlockGameInstance>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		gameInstance->CreateMySession(roomName, playerCount); // �� ����
	}

}
