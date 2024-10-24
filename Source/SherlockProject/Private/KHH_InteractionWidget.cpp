// Fill out your copyright notice in the Description page of Project Settings.


#include "KHH_InteractionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UKHH_InteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UKHH_InteractionWidget::WhenItemClick(int32 value)
{
	ExplainImage->SetBrushFromTexture(ItemTexture[value - 1]);
	FText text1, text2, text3;
	switch ( value )
	{
	case 1:
		text1 = FText::FromString(FString::Printf(TEXT("공사 현장에서 사용하던 곡괭이.")));
		text2 = FText::FromString(FString::Printf(TEXT("날에 피가 묻은 채로 시체 주변에 함께 있었다.")));
		text3 = FText::FromString(FString::Printf(TEXT("피해자의 손목을 잘랐을 때 사용한 것으로 추정된다.")));
		SetExplainText(text1, text2, text3);
		break;
	case 2:
		text1 = FText::FromString(FString::Printf(TEXT("시체를 덮고 있는 포대 위에서 발견된 볼펜.")));
		text2 = FText::FromString(FString::Printf(TEXT("사건 현장 주변 모 자동차 영업사원이 홍보용으로 나눠주었다고 한다.")));
		text3 = FText::FromString(FString::Printf(TEXT("조사 결과 공사장 인부들은 볼펜을 모두 가지고 있었으나, 시체 최초 발견자인 이씨만 볼펜을 가지고 있지 않았다.")));
		SetExplainText(text1, text2, text3);
		break;
	case 3:
		text1 = FText::FromString(FString::Printf(TEXT("시체의 손목에는 있어야할 양 손이 보이지 않는다.")));
		text2 = FText::FromString(FString::Printf(TEXT("아직 현장에서 발견 되지 않았다.")));
		text3 = FText::FromString(FString::Printf(TEXT("")));
		SetExplainText(text1, text2, text3);
		break;
	case 4:
		text1 = FText::FromString(FString::Printf(TEXT("시체의 목에서 발견된 족적.")));
		text2 = FText::FromString(FString::Printf(TEXT("시체 최초 발견자 이 씨가 신던 슬리퍼의 바닥과 유사하다.")));
		text3 = FText::FromString(FString::Printf(TEXT("")));
		SetExplainText(text1, text2, text3);
		break;
	case 5:
		text1 = FText::FromString(FString::Printf(TEXT("피해자의 주머니에서 발견된 현금.")));
		text2 = FText::FromString(FString::Printf(TEXT("현금이 없어지지 않은 것으로 보아 강도의 범행은 아니라고 추정된다.")));
		text3 = FText::FromString(FString::Printf(TEXT("")));
		SetExplainText(text1, text2, text3);
		break;
	case 6:
		text1 = FText::FromString(FString::Printf(TEXT("시체가 있던 공간에서 떨어진 곳에서 발견된 핏자국.")));
		text2 = FText::FromString(FString::Printf(TEXT("잔인한 사건 현장에 비해 핏자국이 별로 없고, 동맥 파열에 의한 비산흔이 없는 것으로 보아 과다 출혈로 인한 사망은 아닐 것이다.")));
		text3 = FText::FromString(FString::Printf(TEXT("")));
		SetExplainText(text1, text2, text3);
		break;
	default:
		text1 = FText::FromString(FString::Printf(TEXT("증거 아직 추가 안됨")));
		text2 = FText::FromString(FString::Printf(TEXT("증거 아직 추가 안됨")));
		text3 = FText::FromString(FString::Printf(TEXT("증거 아직 추가 안됨")));
		SetExplainText(text1, text2, text3);
		break;
	}
	return;
}

void UKHH_InteractionWidget::SetExplainText(FText Text1, FText Text2, FText Text3)
{
	Explain_1->SetText(Text1);
	Explain_2->SetText(Text2);
	Explain_3->SetText(Text3);
}
