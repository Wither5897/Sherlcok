// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_SingleReport.h"
#include "AJH_SherlockGameInstance.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "GameFramework/PlayerState.h"
#include "Components/TextBlock.h"

void UUW_SingleReport::NativeConstruct()
{
	Super::NativeConstruct();

	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());

	auto* gi = Cast<UAJH_SherlockGameInstance>(GetGameInstance());

	APlayerState* ps = me->GetPlayerState();

	float rawPercent = 0;
	if(gi->PlayerCollection.IsValidIndex(ps->GetPlayerId())){
		rawPercent = gi->PlayerCollection[ps->GetPlayerId()];
	}
	
	int32 roundedPercent = FMath::FloorToInt(rawPercent);

	// 퍼센트는 받으면 넣을 예정 
	percent->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), roundedPercent)));

	if ( roundedPercent >= 80 )
	{
		sub->SetText(FText::FromString(*subString[0])); // 퍼센트에 대한 부가적인 설명 (80, 50이상, 50이하)
		EndingMark->SetText(FText::FromString(*EndingMarkArr[0]));
		EndingMarkShadow->SetText(FText::FromString(*EndingMarkShadowArr[0]));
	}

	else if ( roundedPercent >= 50 )
	{
		sub->SetText(FText::FromString(*subString[1])); // 퍼센트에 대한 부가적인 설명 (80, 50이상, 50이하)
		EndingMark->SetText(FText::FromString(*EndingMarkArr[1]));
		EndingMarkShadow->SetText(FText::FromString(*EndingMarkShadowArr[1]));
	}

	else if ( roundedPercent < 50 )
	{
		sub->SetText(FText::FromString(*subString[2])); // 퍼센트에 대한 부가적인 설명 (80, 50이상, 50이하)
		EndingMark->SetText(FText::FromString(*EndingMarkArr[2]));
		EndingMarkShadow->SetText(FText::FromString(*EndingMarkShadowArr[2]));
	}
}
