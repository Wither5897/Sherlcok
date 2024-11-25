// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_EndingCredit.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "AJH_SherlockGameInstance.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "GameFramework/PlayerState.h"
#include "SK/StatisticsWidget.h"

void UUW_EndingCredit::NativeConstruct()
{
	Super::NativeConstruct();

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());

	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());
	APlayerState* ps = me->GetPlayerState();
	
	// 용의자 사진, 용의자 이름, 용의자 관련 설명 가져옴 
	if ( !me || !me->StatisticsUI ) 
	{
		return;
	}
	int32 MostVotedIndex = 0;

	//me->StatisticsUI->CalcSuspectRank();

	if (jobImageTexture.IsValidIndex(MostVotedIndex) && jobString.IsValidIndex(MostVotedIndex))
	{
		jobImage->SetBrushFromTexture(jobImageTexture[MostVotedIndex]); // 직업 사진 
		Job->SetText(FText::FromString(jobString[MostVotedIndex])); // 직업 , 용의자 (0.공사장 노동자, 1. 목수 이씨, 2. 친구 황씨)
	}

	if (SubExplainString.IsValidIndex(MostVotedIndex))
	{
		SubExplain->SetText(FText::FromString(SubExplainString[MostVotedIndex])); // 용의자 이유, 의심 (용의자 배열 순서 동일)
	}
}
