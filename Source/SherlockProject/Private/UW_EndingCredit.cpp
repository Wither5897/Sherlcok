// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_EndingCredit.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUW_EndingCredit::NativeConstruct()
{
	Super::NativeConstruct();


	jobImage->SetBrushFromTexture(jobImageTexture[0]);// 직업 사진 
	Job->SetText(FText::FromString(*jobString[0]));// 직업 

	// 퍼센트는 받으면 넣을 예정 

	sub->SetText(FText::FromString(*subString[1])); // 퍼센트에 대한 부가적인 설명 

}
