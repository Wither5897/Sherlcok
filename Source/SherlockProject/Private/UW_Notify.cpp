// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_Notify.h"
#include "Internationalization/Text.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"
#include "../TP_ThirdPerson/TP_ThirdPersonCharacter.h"

void UUW_Notify::NativeConstruct()
{
	me = Cast<ATP_ThirdPersonCharacter>(GetOwningPlayer()->GetCharacter());
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
		if ( GetWorld() )
		{
			GetWorld()->GetTimerManager().SetTimer(PlaySoundTimerHandle, this, &UUW_Notify::PlayCallSoundWithDelay, 10.3f, false);
		}
		break;

	case 2:
		ctgText = FText::FromString(FString::Printf(TEXT("증거들을 보고 전문가들이 의견을 들려주었습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[1]);
		if ( GetWorld() )
		{
			GetWorld()->GetTimerManager().SetTimer(PlaySoundTimerHandle, this, &UUW_Notify::PlayPoliceSoundWithDelay, 10.3f, false);
		}
		break;

	case 3:
		ctgText = FText::FromString(FString::Printf(TEXT("시체 부검 결과가 나왔습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[2]);
		if ( GetWorld() )
		{
			GetWorld()->GetTimerManager().SetTimer(PlaySoundTimerHandle, this, &UUW_Notify::PlayPoliceSoundWithDelay, 10.3f, false);
		}
		break;

	case 4:
		ctgText = FText::FromString(FString::Printf(TEXT("잘린 손에 대해 시민의 신고가 들어왔습니다.")));
		category->SetText(ctgText);
		category_Image->SetBrushFromTexture(categoryImgArr[3]);
		if ( GetWorld() )
		{
			GetWorld()->GetTimerManager().SetTimer(PlaySoundTimerHandle, this, &UUW_Notify::PlayPoliceSoundWithDelay, 10.3f, false);
		}
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

void UUW_Notify::PlayPoliceSoundWithDelay()
{
	if ( me )
	{
		me->PlayPoliceSound();
	}
}

void UUW_Notify::PlayCallSoundWithDelay()
{
	if ( me )
	{
		me->PlayCallSound();
	}
}
