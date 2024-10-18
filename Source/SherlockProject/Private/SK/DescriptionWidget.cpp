// Fill out your copyright notice in the Description page of Project Settings.


#include "SK/DescriptionWidget.h"
#include "Components/TextBlock.h"

void UDescriptionWidget::NativeConstruct()
{	
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);
}

void UDescriptionWidget::WhenItemClicked(int32 value)
{
	SetVisibility(ESlateVisibility::Visible);
	FText text;
	switch (value)
	{
	case 1:
		text = FText::FromString("Blood");
		SetDescriptionText(text);
		break;
	case 2:
		text = FText::FromString("나는 집에 가고 싶다");
		SetDescriptionText(text);
		break;
	case 3:
		text = FText::FromString("배고프다");
		SetDescriptionText(text);
		break;
	case 4: 
		text = FText::FromString("오늘은 뭘 먹을까");
		SetDescriptionText(text);
		break;
	case 5:
		text = FText::FromString("잠이온다");
		SetDescriptionText(text);
		break;
	case 6:
		text = FText::FromString("...");
		SetDescriptionText(text);
		break;
	case 7:
		text = FText::FromString("테스트 7");
		SetDescriptionText(text);
		break;
	case 8:
		text = FText::FromString("테스트 8");
		SetDescriptionText(text);
		break;
	default:
		break;
	}
	return;
}

void UDescriptionWidget::SetDescriptionText(FText NewText)
{
	ItemDescription->SetText(NewText);
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &UDescriptionWidget::SetUIVisibility, 1.5f);
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
