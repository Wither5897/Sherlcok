// Fill out your copyright notice in the Description page of Project Settings.


#include "Jin/AJH_UserNameWidgetComponent.h"
#include "Jin/AJH_UserNameTagWidget.h"
#include "AJH_SherlockGameInstance.h"

void UAJH_UserNameWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

	UWorld* World = GetWorld();
	if ( World )
	{
		UAJH_SherlockGameInstance* GameInstance = Cast<UAJH_SherlockGameInstance>(World->GetGameInstance());
		if ( GameInstance )
		{
			// 게임 인스턴스에서 닉네임을 받아 캐릭터에 설정
			SetUserName(GameInstance->UserNickName);
		}
	}

}

void UAJH_UserNameWidgetComponent::SetUserName(FString UserName)
{
    UAJH_UserNameTagWidget* UserNameWidget = Cast<UAJH_UserNameTagWidget>(GetUserWidgetObject());
    if ( UserNameWidget )
    {
        UserNameWidget->SetUserName(UserName);
    }
}
