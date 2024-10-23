// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/DescriptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UDescriptionWidget::NativeConstruct()
{	
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &UDescriptionWidget::BackButtonClicked);

	SetVisibility(ESlateVisibility::Hidden);
	
}

void UDescriptionWidget::WhenItemClicked(int32 value)
{
	SetVisibility(ESlateVisibility::Visible);
	FText text;
	if ( value <= 6 ) {
		RealEvidence->SetBrushFromTexture(RealEvidenceArray[value - 1]);
	}
	switch (value)
	{
	case 1:
		text = FText::FromString(FString::Printf(TEXT("공사 현장에서 사용하던 곡괭이. 날에 피가 묻은 채로 시체 주변에 함께 있었다. 피해자의 손목을 잘랐을 때 사용한 것으로 추정된다.")));
		SetDescriptionText(text);
		break;
	case 2:
		text = FText::FromString(FString::Printf(TEXT("시체를 덮고 있는 포대 위에서 발견된 볼펜. 사건 현장 주변 모 자동차 영업사원이 홍보용으로 나눠주었다고 한다. 조사 결과 공사장 인부들은 볼펜을 모두 가지고 있었으나, 시체 최초 발견자인 이씨만 볼펜을 가지고 있지 않았다.")));
		SetDescriptionText(text);
		break;
	case 3:
		text = FText::FromString(FString::Printf(TEXT("시체의 손목에는 있어야할 양 손이 보이지 않는다. 아직 현장에서 발견 되지 않았다.")));
		SetDescriptionText(text);
		break;
	case 4: 
		text = FText::FromString(FString::Printf(TEXT("시체의 목에서 발견된 족적. 시체 최초 발견자 이 씨가 신던 슬리퍼의 바닥과 유사하다.")));
		SetDescriptionText(text);
		break;
	case 5:
		text = FText::FromString(FString::Printf(TEXT("피해자의 주머니에서 발견된 현금. 현금이 없어지지 않은 것으로 보아 강도의 범행은 아니라고 추정된다.")));
		SetDescriptionText(text);
		break;
	case 6:
		text = FText::FromString(FString::Printf(TEXT("시체가 있던 공간에서 떨어진 곳에서 발견된 핏자국. 잔인한 사건 현장에 비해 핏자국이 별로 없고, 동맥 파열에 의한 비산흔이 없는 것으로 보아 과다 출혈로 인한 사망은 아닐 것이다.")));
		SetDescriptionText(text);
		break;
	case 7:
		text = FText::FromString(FString::Printf(TEXT("테스트 7")));
		SetDescriptionText(text);
		break;
	case 8:
		text = FText::FromString(FString::Printf(TEXT("테스트 8")));
		SetDescriptionText(text);
		break;
	default:
		text = FText::FromString(FString::Printf(TEXT("테스트 9 ~ 16")));
		SetDescriptionText(text);
		break;
	}
	return;
}

void UDescriptionWidget::SetDescriptionText(FText NewText)
{
	ItemDescription->SetText(NewText);
	/*FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UDescriptionWidget::SetUIVisibility, 1.5f);*/
}

void UDescriptionWidget::SetUIVisibility()
{
	if (IsVisible()) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UDescriptionWidget::BackButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}
