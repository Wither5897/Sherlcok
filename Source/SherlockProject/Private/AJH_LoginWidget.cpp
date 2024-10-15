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
		// 누를때 닉네임과 캐릭터 선택값을 저장하기
		gi->UserNickName = Edit_hostName->GetText().ToString();
		gi->FindMySession();
	}
}

void UAJH_LoginWidget::OnClickedResetButton()
{
	// 지금현재있는 방들 삭제 하고
	// 내가 속해있는 세션도 나가고
	gi->ExitMySession();
	// 룸만들기
	//gi->CreateMySession();
	gi->OnDestroyAllSessions();
}
