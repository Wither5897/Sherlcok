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
	int32 MostVotedIndex = me->StatisticsUI->CalcSuspectRank();

	if ( jobImageTexture.IsValidIndex(MostVotedIndex) && jobString.IsValidIndex(MostVotedIndex) )
	{
		jobImage->SetBrushFromTexture(jobImageTexture[MostVotedIndex]); // 직업 사진 
		Job->SetText(FText::FromString(jobString[MostVotedIndex])); // 직업 , 용의자 (0.공사장 노동자, 1. 목수 이씨, 2. 친구 황씨)
	}

	if ( SubExplainString.IsValidIndex(MostVotedIndex) && subString.IsValidIndex(MostVotedIndex) )
	{
		SubExplain->SetText(FText::FromString(SubExplainString[MostVotedIndex])); // 용의자 이유, 의심 (용의자 배열 순서 동일)
	}

	//// 퍼센트는 받으면 넣을 예정 
	////percent->SetText(FText::FromString(FString::Printf(TEXT("%f"), gi->PlayerCollection[ps->GetPlayerId()]))); 

	//sub->SetText(FText::FromString(*subString[1])); // 퍼센트에 대한 부가적인 설명 (80, 50이상, 50이하)

}
