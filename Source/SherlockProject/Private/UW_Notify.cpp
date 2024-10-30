// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Notify.h"
#include "Internationalization/Text.h"
#include "Components/TextBlock.h"

void UUW_Notify::NativeConstruct()
{

}

void UUW_Notify::notifySetting(int32 value)
{
	FText ctgText;	
	switch ( value )
	{
	case 1:
		// font size30, red
		ctgText = FText::FromString(FString::Printf(TEXT("사건 발생 18년만에 목격자가 진술했습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[0]);
		break;

	case 2:
		ctgText = FText::FromString(FString::Printf(TEXT("증거들을 보고 전문가들이 의견을 들려주었습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[1]);
		break;

	case 3:
		ctgText = FText::FromString(FString::Printf(TEXT("시체 부검 결과가 나왔습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[2]);
		break;

	case 4:
		ctgText = FText::FromString(FString::Printf(TEXT("잘린 손에 대해 시민의 신고가 들어왔습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[3]);
		break;

	default:
		break;
	}
	return;
}

void UUW_Notify::PlayNotifyAnim()
{
	if ( Notifyinfo )
	{
		PlayAnimation(Notifyinfo);
	}
}
