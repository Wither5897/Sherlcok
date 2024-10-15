// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AJH_SherlockGameInstance.h"

void UAJH_LoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	Btn_findSessions->OnClicked.AddDynamic(this, &UAJH_LoginWidget::OnClickedFindSessionsButton);
	
}

void UAJH_LoginWidget::OnClickedFindSessionsButton()
{
	if (gi != nullptr)
	{
		// ������ �г��Ӱ� ĳ���� ���ð��� �����ϱ�
		gi->UserNickName = Edit_hostName->GetText().ToString();
		gi->FindMySession();
	}
}

void UAJH_LoginWidget::OnClickedResetButton()
{
	// ���������ִ� ��� ���� �ϰ�
	// ���� �����ִ� ���ǵ� ������
	gi->ExitMySession();
	// �븸���
	//gi->CreateMySession();
	gi->OnDestroyAllSessions();
}
