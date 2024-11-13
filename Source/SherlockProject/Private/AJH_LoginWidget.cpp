// Fill out your copyright notice in the Description page of Project Settings.


#include "AJH_LoginWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "AJH_SherlockGameInstance.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"

void UAJH_LoginWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Switcher_Opening->SetActiveWidgetIndex(0);
	gi = GetGameInstance<UAJH_SherlockGameInstance>();
	Btn_findSessions->OnClicked.AddDynamic(this, &UAJH_LoginWidget::OnClickedFindSessionsButton);
	//Edit_hostName->OnTextChanged.AddDynamic(this, &UAJH_LoginWidget::OnMyTextChanged);
}

void UAJH_LoginWidget::OnClickedFindSessionsButton()
{
	UGameplayStatics::PlaySound2D(GetWorld(), MainbuttonSound);
	if (gi != nullptr)
	{
		// 누를때 닉네임과 캐릭터 선택값을 저장하기
		gi->UserNickName = Edit_hostName->GetText().ToString();
		auto* pc = GetOwningPlayer();
		pc->ClientTravel("/Game/KHH/CharacterCustom/EditMap?Listen", TRAVEL_Absolute);
		// gi->FindMySession();
	}
}

void UAJH_LoginWidget::OnClickedResetButton()
{
	// 지금현재있는 방들 삭제 하고
	// 내가 속해있는 세션도 나가고
	gi->ExitMySession();
	// 룸만들기
	gi->OnDestroyAllSessions();
}

void UAJH_LoginWidget::OnMyTextChanged(const FText& InText)
{
	if ( !InText.IsEmpty() )
	{
		Edit_hostName->SetText(InText);
	}
}
